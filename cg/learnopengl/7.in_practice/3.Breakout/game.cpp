#include <algorithm>
#include <sstream>
#include <iostream>

#include "filesystem.h"

#include "irrKlang.h"
using namespace irrklang;

#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "ball_object.h"
#include "particle_generator.h"
#include "post_processor.h"
#include "text_renderer.h"

SpriteRenderer *Renderer;
GameObject *Player;
BallObject *Ball;
ParticleGenerator *Particles;
PostProcessor *Effects;
ISoundEngine *SoundEngine = createIrrKlangDevice();
TextRenderer *Text;

float ShakeTime = 0.0f;

Game::Game(unsigned int width, unsigned int height)
  : State(GAME_MENU),
    Keys(),
    KeysProcessed(),
    Width(width),
    Height(height),
    Level(0),
    Lives(3)
{
  //std::string a = FileSystem::getPath("learnopengl/resources/audio/breakout.mp3");
  //std::cout << "a = " << a << std::endl;
}

Game::~Game() {
  delete Renderer;
  delete Player;
  delete Ball;
  delete Particles;
  delete Effects;
  delete Text;
  SoundEngine->drop();
}

void Game::Init() {
  // load shaders
  ResourceManager::LoadShader("sprite.vs", "sprite.fs", nullptr, "sprite");
  ResourceManager::LoadShader("particle.vs", "particle.fs", nullptr, "particle");
  ResourceManager::LoadShader("post_processing.vs", "post_processing.fs",
      nullptr, "postprocessing");

  // configure shaders
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
      static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
  ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
  ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
  ResourceManager::GetShader("particle").Use().SetInteger("particle", 0);
  ResourceManager::GetShader("particle").Use().SetMatrix4("projection", projection);

  // load textures
  ResourceManager::LoadTexture(
      FileSystem::getPath("learnopengl/resources/textures/background.jpg").c_str(),
      false,
      "background");
  ResourceManager::LoadTexture(
      FileSystem::getPath("learnopengl/resources/textures/awesomeface.png").c_str(),
      true,
      "face");
  ResourceManager::LoadTexture(
      FileSystem::getPath("learnopengl/resources/textures/block.png").c_str(),
      false,
      "block");
  ResourceManager::LoadTexture(
      FileSystem::getPath("learnopengl/resources/textures/block_solid.png").c_str(),
      false,
      "block_solid");
  ResourceManager::LoadTexture(
      FileSystem::getPath("learnopengl/resources/textures/paddle.png").c_str(),
      true,
      "paddle");
  ResourceManager::LoadTexture(
      FileSystem::getPath("learnopengl/resources/textures/particle.png").c_str(),
      true,
      "particle");
  ResourceManager::LoadTexture(
      FileSystem::getPath("learnopengl/resources/textures/powerup_speed.png").c_str(),
      true,
      "powerup_speed");
  ResourceManager::LoadTexture(
      FileSystem::getPath("learnopengl/resources/textures/powerup_sticky.png").c_str(),
      true,
      "powerup_sticky");
  ResourceManager::LoadTexture(
      FileSystem::getPath("learnopengl/resources/textures/powerup_increase.png").c_str(),
      true,
      "powerup_increase");
  ResourceManager::LoadTexture(
      FileSystem::getPath("learnopengl/resources/textures/powerup_confuse.png").c_str(),
      true,
      "powerup_confuse");
  ResourceManager::LoadTexture(
      FileSystem::getPath("learnopengl/resources/textures/powerup_chaos.png").c_str(),
      true,
      "powerup_chaos");
  ResourceManager::LoadTexture(
      FileSystem::getPath("learnopengl/resources/textures/powerup_passthrough.png").c_str(),
      true,
      "powerup_passthrough");

  // set render-specific controls
  Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
  Particles = new ParticleGenerator(ResourceManager::GetShader("particle"),
      ResourceManager::GetTexture("particle"), 500);
  Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"),
      this->Width, this->Height);
  Text = new TextRenderer(this->Width, this->Height);
  Text->Load(
      FileSystem::getPath("learnopengl/resources/fonts/OCRAEXT.TTF").c_str(),
      24);

  // load levels
  GameLevel one;
  one.Load(
      FileSystem::getPath("learnopengl/resources/levels/one.lvl").c_str(),
      this->Width,
      this->Height / 2);

  GameLevel two;
  two.Load(
      FileSystem::getPath("learnopengl/resources/levels/two.lvl").c_str(),
      this->Width,
      this->Height / 2);

  GameLevel three;
  three.Load(
      FileSystem::getPath("learnopengl/resources/levels/three.lvl").c_str(),
      this->Width,
      this->Height / 2);

  GameLevel four;
  four.Load(
      FileSystem::getPath("learnopengl/resources/levels/four.lvl").c_str(),
      this->Width,
      this->Height / 2);

  this->Levels.push_back(one);
  this->Levels.push_back(two);
  this->Levels.push_back(three);
  this->Levels.push_back(four);
  this->Level = 0;

  // configure game objects
  glm::vec2 playerPos = glm::vec2(
      this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
      this->Height - PLAYER_SIZE.y);
  Player = new GameObject(
      playerPos,
      PLAYER_SIZE,
      ResourceManager::GetTexture("paddle"));

  glm::vec2 ballPos = playerPos + glm::vec2(
      PLAYER_SIZE.x / 2.0f - BALL_RADIUS,
      -BALL_RADIUS * 2.0f);
  Ball = new BallObject(
      ballPos,
      BALL_RADIUS,
      INITIAL_BALL_VELOCITY,
      ResourceManager::GetTexture("face"));

  // audio
  std::string breakoutMP3Path = FileSystem::getPath("learnopengl/resources/audio/breakout.mp3").c_str();
  std::cout << "breakoutMP3Path: " << breakoutMP3Path << std::endl;
  SoundEngine->play2D(
      FileSystem::getPath("learnopengl/resources/audio/breakout.mp3").c_str(),
      true);
}

void Game::ProcessInput(float dt) {
  if (this->State == GAME_ACTIVE) {
    float velocity = PLAYER_VELOCITY * dt;
    if (this->Keys[GLFW_KEY_A]) {
      if (Player->Position.x >= 0.0f) {
        Player->Position.x -= velocity;
        if (Ball->Stuck) {
          Ball->Position.x -= velocity;
        }
      }
    }
    if (this->Keys[GLFW_KEY_D]) {
      if (Player->Position.x <= this->Width - Player->Size.x) {
        Player->Position.x += velocity;
        if (Ball->Stuck) {
          Ball->Position.x += velocity;
        }
      }
    }
    if (this->Keys[GLFW_KEY_SPACE]) {
      Ball->Stuck = false;
    }
  } else if (this->State == GAME_WIN) {
    if (this->Keys[GLFW_KEY_ENTER]) {
      this->KeysProcessed[GLFW_KEY_ENTER] = true;
      Effects->Chaos = false;
      this->State = GAME_MENU;
    }
  } else if (this->State == GAME_MENU) {
    if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER]) {
      this->State = GAME_ACTIVE;
      this->KeysProcessed[GLFW_KEY_ENTER] = true;
    }
    if (this->Keys[GLFW_KEY_W] && !this->KeysProcessed[GLFW_KEY_W]) {
      this->Level = (this->Level + 1) % 4;
      this->KeysProcessed[GLFW_KEY_W] = true;
    }
    if (this->Keys[GLFW_KEY_S] && !this->KeysProcessed[GLFW_KEY_S]) {
      if (this->Level > 0) {
        this->Level -= 1;
      } else {
        this->Level = 3;
      }
      this->KeysProcessed[GLFW_KEY_S] = true;
    }
  } else {
  }
}

void Game::Update(float dt) {
  Ball->Move(dt, this->Width);

  this->DoCollisions();

  Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2.0f));

  this->UpdatePowerUps(dt);

  if (ShakeTime > 0.0f) {
    ShakeTime -= dt;
    if (ShakeTime <= 0.0f) {
      Effects->Shake = false;
    }
  }

  if (Ball->Position.y >= this->Height) {
    --this->Lives;
    if (this->Lives == 0) {
      this->ResetLevel();
      this->State = GAME_MENU;
    }
    this->ResetPlayer();
  }

  if (this->State == GAME_ACTIVE && this->Levels[this->Level].IsCompleted()) {
    this->ResetLevel();
    this->ResetPlayer();
    Effects->Chaos = true;
    this->State = GAME_WIN;
  }
}

void Game::Render() {
  if (this->State == GAME_ACTIVE ||
      this->State == GAME_MENU ||
      this->State == GAME_WIN) {

    Effects->BeginRender();

    Renderer->DrawSprite(
        ResourceManager::GetTexture("background"),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(this->Width, this->Height),
        0.0f);

    this->Levels[this->Level].Draw(*Renderer);

    Player->Draw(*Renderer);

    for (PowerUp &powerup : this->PowerUps) {
      if (!powerup.Destroyed) {
        powerup.Draw(*Renderer);
      }
    }

    Particles->Draw();

    Ball->Draw(*Renderer);

    Effects->EndRender();
    Effects->Render(glfwGetTime());

    std::stringstream ss;
    ss << this->Lives;
    Text->RenderText("Lives:" + ss.str(), 5.0f, 5.0f, 1.0f);
  }

  if (this->State == GAME_MENU) {
    Text->RenderText("Press ENTER to start", 250.0f, this->Height / 2.0f, 1.0f);
    Text->RenderText("Press W or S to select level", 245.0f, this->Height / 2.0f + 20.0f, 0.75f);
  }

  if (this->State == GAME_WIN) {
    Text->RenderText("You WON!!!", 320.0f, this->Height / 2.0f - 20.0f,
        1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    Text->RenderText("Press ENTER to retry or ESC to quit", 130.0f, this->Height / 2.0f,
        1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
  }
}

void ActivatePowerUp(PowerUp &powerUp) {
  if (powerUp.Type == "speed") {
    Ball->Velocity *= 1.2;
  } else if (powerUp.Type == "sticky") {
    Ball->Sticky = true;
    Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
  } else if (powerUp.Type == "pass-through") {
    Ball->PassThrough = true;
    Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
  } else if (powerUp.Type == "pad-size-increase") {
    Player->Size.x += 50;
  } else if (powerUp.Type == "confuse") {
    if (!Effects->Chaos) {
      Effects->Confuse = true;
    }
  } else if (powerUp.Type == "chaos") {
    if (!Effects->Confuse) {
      Effects->Chaos = true;
    }
  }
}

bool CheckCollision(GameObject &one, GameObject &two);
Collision CheckCollision(BallObject &one, GameObject &two);
Direction VectorDirection(glm::vec2 closest);

void Game::DoCollisions() {
  for (GameObject &box : this->Levels[this->Level].Bricks) {
    if (!box.Destroyed) {
      Collision collision = CheckCollision(*Ball, box);
      if (std::get<0>(collision)) {
        if (!box.IsSolid) {
          box.Destroyed = true;
          this->SpawnPowerUps(box);
          SoundEngine->play2D(FileSystem::getPath("learnopengl/resources/audio/bleep.mp3").c_str(), false);
        } else {
          ShakeTime = 0.05f;
          Effects->Shake = true;
          SoundEngine->play2D(FileSystem::getPath("learnopengl/resources/audio/bleep.mp3").c_str(), false);
        }
        Direction dir = std::get<1>(collision);
        glm::vec2 diff_vector = std::get<2>(collision);
        if (!(Ball->PassThrough && !box.IsSolid)) {
          if (dir == LEFT || dir == RIGHT) {
            Ball->Velocity.x = -Ball->Velocity.x;
            float penetration = Ball->Radius - std::abs(diff_vector.x);
            if (dir == LEFT) {
              Ball->Position.x += penetration;
            } else {
              Ball->Position.x -= penetration;
            }
          } else {
            Ball->Velocity.y = -Ball->Velocity.y;
            float penetration = Ball->Radius - std::abs(diff_vector.y);
            if (dir == UP) {
              Ball->Position.y -= penetration;
            } else {
              Ball->Position.y += penetration;
            }
          }
        }
      }
    }
  }

  for (PowerUp &powerUp : this->PowerUps) {
    if (!powerUp.Destroyed) {
      if (powerUp.Position.y >= this->Height) {
        powerUp.Destroyed = true;
      }

      if (CheckCollision(*Player, powerUp)) {
        ActivatePowerUp(powerUp);
        powerUp.Destroyed = true;
        powerUp.Activated = true;
        SoundEngine->play2D(FileSystem::getPath("learnopengl/resources/audio/powerup.wav").c_str(), false);
      }
    }
  }

  Collision result = CheckCollision(*Ball, *Player);
  if (!Ball->Stuck && std::get<0>(result)) {
    float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
    float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
    float percentage = distance / (Player->Size.x / 2.0f);

    float strength = 2.0f;
    glm::vec2 oldVelocity = Ball->Velocity;
    Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
    Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
    Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);

    Ball->Stuck = Ball->Sticky;

    SoundEngine->play2D(FileSystem::getPath("learnopengl/resources/audio/bleep.wav").c_str(), false);
  }
}

bool CheckCollision(GameObject &one, GameObject &two) {
  bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
    two.Position.x + two.Size.x >= one.Position.x;
  bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
    two.Position.y + two.Size.y >= one.Position.y;
  return collisionX && collisionY;
}

Collision CheckCollision(BallObject &one, GameObject &two) {
  glm::vec2 center(one.Position + one.Radius);

  glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
  glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x,
                        two.Position.y + aabb_half_extents.y);

  glm::vec2 difference = center - aabb_center;
  glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

  glm::vec2 closest = aabb_center + clamped;
  difference = closest - center;

  if (glm::length(difference) < one.Radius) {
    return std::make_tuple(true, VectorDirection(difference), difference);
  } else {
    return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
  }
}

Direction VectorDirection(glm::vec2 target) {
  glm::vec2 compass[] = {
    glm::vec2(0.0f, 1.0f), // up
    glm::vec2(1.0f, 0.0f), // right
    glm::vec2(0.0f, -1.0f), // down
    glm::vec2(-1.0f, 0.0f), // left
  };
  float max = 0.0f;
  unsigned int best_match = -1;
  for (unsigned int i = 0; i < 4; ++i) {
    float dot_product = glm::dot(glm::normalize(target), compass[i]);
    if (dot_product > max) {
      max = dot_product;
      best_match = i;
    }
  }
  return (Direction)best_match;
}

void Game::ResetLevel() {
  if (this->Level == 0) {
    this->Levels[0].Load("levels/one.lvl", this->Width, this->Height / 2);
  } else if (this->Level == 1) {
    this->Levels[1].Load("levels/two.lvl", this->Width, this->Height / 2);
  } else if (this->Level == 2) {
    this->Levels[2].Load("levels/three.lvl", this->Width, this->Height / 2);
  } else if (this->Level == 3) {
    this->Levels[3].Load("levels/four.lvl", this->Width, this->Height / 2);
  }

  this->Lives = 3;
}

void Game::ResetPlayer() {
  Player->Size = PLAYER_SIZE;
  Player->Position = glm::vec2(
      this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
      this->Height - PLAYER_SIZE.y);
  Ball->Reset(
      Player->Position +
      glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS,
                -(BALL_RADIUS * 2.0f)),
      INITIAL_BALL_VELOCITY);

  Effects->Chaos = false;
  Effects->Confuse = false;
  Ball->PassThrough = false;
  Ball->Sticky = false;
  Player->Color = glm::vec3(1.0f);
  Ball->Color = glm::vec3(1.0f);
}

bool ShouldSpawn(unsigned int chance) {
  unsigned int random = rand() % chance;
  return random == 0;
}

void Game::SpawnPowerUps(GameObject &block) {
  if (ShouldSpawn(75)) {
    this->PowerUps.push_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f),
          0.0f, block.Position, ResourceManager::GetTexture("powerup_speed")));
  }

  if (ShouldSpawn(75)) {
    this->PowerUps.push_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f),
          20.0f, block.Position, ResourceManager::GetTexture("powerup_sticky")));
  }

  if (ShouldSpawn(75)) {
    this->PowerUps.push_back(PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f),
          10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough")));
  }

  if (ShouldSpawn(75)) {
    this->PowerUps.push_back(PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4f),
          0.0f, block.Position, ResourceManager::GetTexture("powerup_increase")));
  }

  if (ShouldSpawn(15)) {
    this->PowerUps.push_back(PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f),
          15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse")));
  }

  if (ShouldSpawn(15)) {
    this->PowerUps.push_back(PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f),
          15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos")));
  }
}

bool IsOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type);

void Game::UpdatePowerUps(float dt) {
  for (PowerUp &powerUp : this->PowerUps) {
    powerUp.Position += powerUp.Velocity * dt;
    if (powerUp.Activated) {
      powerUp.Duration -= dt;
      if (powerUp.Duration <= 0.0f) {
        powerUp.Activated = false;
        if (powerUp.Type == "sticky") {
          if (!IsOtherPowerUpActive(this->PowerUps, "sticky")) {
            Ball->Sticky = false;
            Player->Color = glm::vec3(1.0f);
          }
        } else if (powerUp.Type == "pass-through") {
          if (!IsOtherPowerUpActive(this->PowerUps, "pass-through")) {
            Ball->PassThrough = false;
            Ball->Color = glm::vec3(1.0f);
          }
        } else if (powerUp.Type == "confuse") {
          if (!IsOtherPowerUpActive(this->PowerUps, "confuse")) {
            Effects->Confuse = false;
          }
        } else if (powerUp.Type == "chaos") {
          if (!IsOtherPowerUpActive(this->PowerUps, "chaos")) {
            Effects->Chaos = false;
          }
        }
      }
    }
  }

  this->PowerUps.erase(std::remove_if(
        this->PowerUps.begin(),
        this->PowerUps.end(),
        [](const PowerUp &powerUp) {
          return powerUp.Destroyed && !powerUp.Activated;
        }), this->PowerUps.end());
}

bool IsOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type) {
  for (const PowerUp &powerup : powerUps) {
    if (powerup.Activated) {
      if(powerup.Type == type) {
        return true;
      }
    }
  }
  return false;
}
