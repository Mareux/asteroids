
#include "game.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define MAP_WIDTH 2000
#define MAP_HEIGHT 2000

using namespace std;

double random_between_two_double(double min, double max) {
    return (min + 1) + (((double) rand()) / (double) RAND_MAX) * (max - (min + 1));
}

int randomInt(int outerMin, int outerMax, int innerMin, int innerMax) {
    auto usableRange = innerMin - outerMin + outerMax - innerMax;
    auto threshold = innerMin - outerMin;
    auto num = floor(rand() % (usableRange + 1));

    if (num < threshold)
        return num;
    return num - threshold + innerMax;
}

/* Test Framework realization */
class MyFramework : public Framework {
private:
    Sprite *bigAsteroid;
    Sprite *smallAsteroid;
    Sprite *shipSprite;
    Sprite *bulletSprite;
    Sprite *cursor;

    vector<Sprite *> abilitySprites;
    vector<Asteroid> asteroids;
    Ship *ship;

    const int FRAMES_PER_SECOND = 60;
    const int FRAME_CONTROL = (1000 / FRAMES_PER_SECOND);
    double lastFrameTime = 0;
    double currentFrameTime;

    int mouse_x, mouse_y;
    double cameraX = 0;
    double cameraY = 0;
    int timer = 0;
    int widthSmall, heightSmall;
    int widthBig, heightBig;
    int cursorW, cursorH;

    int mapHeight, mapWidth;
    int screenWidth, screenHeight;
    int numAmmo, numAsteroids;
    double abilityProbability;

    bool abilityUsed = false;
    bool gameOver = false;

    Asteroid addSmallAsteroid() {
        Asteroid asteroid = Asteroid(false);
        asteroid.setObjectSize(widthSmall, heightSmall);
        return asteroid;
    }

    Asteroid addBigAsteroid() {
        Asteroid asteroid = Asteroid(true);
        asteroid.setObjectSize(widthBig, heightBig);
        return asteroid;
    }

    vector<Asteroid> createAsteroids(int asteroidQuantity) {
        vector<Asteroid> asteroid;

        int width, height;

        cout << asteroidQuantity << endl;

        for (auto i = 0; i < asteroidQuantity; ++i) {
            bool big = rand() % 2;

            if (big) {
                asteroid.emplace_back(addBigAsteroid());
            } else
                asteroid.emplace_back(addSmallAsteroid());

            asteroid.at(i).setPositionX(randomInt(0, mapWidth,
                    screenWidth / 2 - 50, screenWidth / 2 + 50));
            asteroid.at(i).setPositionY(randomInt(0, mapHeight,
                    screenHeight / 2 - 50, screenHeight / 2 + 50));
            asteroid.at(i).setDirection(random_between_two_double(-2, 1),
                                        random_between_two_double(-2, 1));
            asteroid.at(i).setSpeed(random_between_two_double(0, 4));
        }

        return asteroid;

    }

    void dealWithBulletCollision() {
        std::__wrap_iter<Asteroid *> asteroidPos;

        if (ship->checkBulletCollision(asteroids, asteroidPos)) {
            double x = asteroidPos->getLeftUpX();
            double y = asteroidPos->getLeftUpY();

            if (asteroidPos->isBig()) {

                double dirX = asteroidPos->getDirectionX();
                double dirY = asteroidPos->getDirectionY();

                double speed = asteroidPos->getSpeed();

                auto sin30 = -0.98803162409;
                auto cos30 = 0.15425144988;

                asteroids.erase(asteroidPos);

                asteroids.emplace_back(addSmallAsteroid());
                auto asteroid = asteroids.size() - 1;

                auto dx = dirX * cos30 - dirY * sin30;
                auto dy = dirX * sin30 + dirY * cos30;

                asteroids.at(asteroid).setDirection(dx, dy);
                asteroids.at(asteroid).setPositionY(y - 10);
                asteroids.at(asteroid).setPositionX(x - 10);
                asteroids.at(asteroid).setSpeed(speed);

                asteroids.emplace_back(addSmallAsteroid());
                asteroid = asteroids.size() - 1;

                dx = dirX * cos30 + dirY * sin30;
                dy = dirX * -sin30 + dirY * cos30;

                asteroids.at(asteroid).setDirection(dx, dy);
                asteroids.at(asteroid).setPositionY(y + 10);
                asteroids.at(asteroid).setPositionX(x + 10);
                asteroids.at(asteroid).setSpeed(speed);

            } else {
                asteroids.erase(asteroidPos);
            }

            if (rand() % 100 < abilityProbability * 100) {
                ship->createAbility(x, y, 20, 20);
            }
        }
    }

    void moveCamera() {

        ship->applyVelocity(cameraX, cameraY);

        if (ship->getRightDownX() - cameraX < 0)
            cameraX = mapWidth - screenWidth;
        else if (ship->getLeftUpX() - cameraX > screenWidth)
            cameraX = 0;
        if (ship->getRightDownY() - cameraY < 0)
            cameraY = mapHeight - screenHeight;
        else if (ship->getLeftUpY() - cameraY > screenHeight)
            cameraY = 0;

        if (cameraX < 0 || ship->getLeftUpX() < screenWidth / 2) {
            cameraX = 0;
        } else if (cameraX + screenWidth > mapWidth || mapWidth - ship->getLeftUpX() < screenWidth / 2) {
            cameraX = mapWidth - screenWidth;
        }
        if (cameraY < 0 || ship->getLeftUpY() < screenHeight / 2) {
            cameraY = 0;
        } else if (cameraY + screenHeight > mapHeight || mapHeight - ship->getLeftUpY() < screenHeight / 2) {
            cameraY = mapHeight - screenHeight;
        }
    }

    static void moveAsteroids(vector<Asteroid> &asteroid, Sprite *asteroidSprite, int screen_w, int screen_h) {

        for (auto &iter : asteroid) {
            iter.getObjectFromUnderworld(screen_w, screen_h);
            iter.movement();
        }
    }

    void createShip() {
        int width, height;

        getSpriteSize(shipSprite, width, height);
        ship = new Ship(screenWidth / 2.0, screenHeight / 2.0, 0.0, 0, 0, width, height, numAmmo);
    }

    static void splitUpAsteroids(Asteroid &firstAsteroid, Asteroid &secondAsteroid) {
        double tmpDirX = firstAsteroid.getDirectionX();
        double tmpDirY = firstAsteroid.getDirectionY();
        double tmpSpeed = firstAsteroid.getSpeed();

        auto dirX = firstAsteroid.getLeftUpX() - secondAsteroid.getLeftUpX();
        auto dirY = firstAsteroid.getLeftUpY() - secondAsteroid.getLeftUpY();

        auto length = sqrt(dirX * dirX + dirY * dirY);
        auto normalDirX = dirX / length;
        auto normalDirY = dirY / length;

        firstAsteroid.setPositionX(firstAsteroid.getLeftUpX() + firstAsteroid.getSpeed() * normalDirX +
                                   secondAsteroid.getDirectionX() * secondAsteroid.getSpeed());
        firstAsteroid.setPositionY(firstAsteroid.getLeftUpY() + firstAsteroid.getSpeed() * normalDirY +
                                   secondAsteroid.getDirectionY() * secondAsteroid.getSpeed());

        firstAsteroid.setDirection(secondAsteroid.getDirectionX(), secondAsteroid.getDirectionY());
        firstAsteroid.setSpeed(secondAsteroid.getSpeed());
        secondAsteroid.setDirection(tmpDirX, tmpDirY);
        secondAsteroid.setSpeed(tmpSpeed);

    }

    static void asteroidsCollision(vector<Asteroid> &asteroid) {
        for (auto firstIter = 0; firstIter < asteroid.size(); ++firstIter) {
            for (auto secondIter = firstIter + 1; secondIter < asteroid.size(); ++secondIter) {
                if (asteroid[firstIter].collision(asteroid[secondIter].getLeftUpX(),
                                                  asteroid[secondIter].getLeftUpY(),
                                                  asteroid[secondIter].getWidth(),
                                                  asteroid[secondIter].getHeight())) {
                    splitUpAsteroids(asteroid[firstIter], asteroid[secondIter]);
                }
            }
        }
    }

    bool shipCollision() {

        for (auto &asteroid : asteroids) {
            if (ship->collision(asteroid.getLeftUpX(), asteroid.getLeftUpY(),
                                asteroid.getWidth(), asteroid.getHeight()))
                return true;
        }
        return false;
    }

    void restart() {
        asteroids.clear();
        delete ship;

        gameOver = false;
        abilityUsed = false;
        cameraX = 0;
        cameraY = 0;
        asteroids = createAsteroids(numAsteroids);
        createShip();
    }

public:

    MyFramework(int screen_width, int screen_height, int map_width, int map_height,
                int num_ammo, int num_asteroids, double ability_probability) {
        screenWidth = screen_width;
        screenHeight = screen_height;
        mapWidth = map_width;
        mapHeight = map_height;
        numAmmo = num_ammo;
        numAsteroids = num_asteroids;
        abilityProbability = ability_probability;
    }

    virtual void PreInit(int &width, int &height, bool &fullscreen) {
        width = screenWidth;
        height = screenHeight;
        fullscreen = false;
    }

    virtual bool Init() {

        srand(time(0));

        bigAsteroid = createSprite("data/big_asteroid.png");
        smallAsteroid = createSprite("data/small_asteroid.png");
        shipSprite = createSprite("data/spaceship.png");
        bulletSprite = createSprite("data/bullet.png");
        cursor = createSprite("data/circle.tga");
        abilitySprites.push_back(createSprite("data/shield.png"));;
        abilitySprites.push_back(createSprite("data/sparkle.png"));

        getSpriteSize(bigAsteroid, widthBig, heightBig);
        getSpriteSize(smallAsteroid, widthSmall, heightSmall);

        asteroids = createAsteroids(numAsteroids);
        createShip();

        getSpriteSize(cursor, cursorW, cursorH);
        showCursor(false);

        return true;
    }

    virtual void Close() {
//        system("leaks Project2");
    }

    virtual bool Tick() {
//		drawTestBackground();

        currentFrameTime = getTickCount();

        if ((currentFrameTime - lastFrameTime) >= FRAME_CONTROL) {
            lastFrameTime = currentFrameTime;


            moveCamera();
            ship->getObjectFromUnderworld(mapWidth, mapHeight);
            ship->shipMovement();


            moveAsteroids(asteroids, smallAsteroid, mapWidth, mapHeight);
            asteroidsCollision(asteroids);

            if (shipCollision())
                gameOver = true;

            ship->moveBullet(mapWidth, mapHeight);
            dealWithBulletCollision();

            if (!abilityUsed) {
                ship->getAbility();
                timer = 600;
            }
            if (abilityUsed) {
                ship->useAbility(asteroids);
                --timer;
                if (timer == 0) {
                    ship->deleteCurrentAbility();
                    abilityUsed = false;
                }
            }
        }

        for (auto &asteroid : asteroids) {
            if (asteroid.isBig())
                drawSprite(bigAsteroid, asteroid.getScreenX() - cameraX, asteroid.getScreenY() - cameraY);
            else
                drawSprite(smallAsteroid, asteroid.getScreenX() - cameraX, asteroid.getScreenY() - cameraY);
        }

        drawSprite(cursor, mouse_x - cursorW / 2, mouse_y - cursorH / 2);
        ship->drawAbility(abilitySprites, cameraX, cameraY, abilityUsed);
        drawSprite(shipSprite, ship->getScreenX() - cameraX, ship->getScreenY() - cameraY);
        ship->drawBullet(bulletSprite, cameraX, cameraY);
        if (gameOver || asteroids.size() == 0)
            restart();
        return false;
    }

    virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
        mouse_x = x;
        mouse_y = y;
    }

    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
        if (button == FRMouseButton::LEFT && !isReleased) {
            ship->createBullet(mouse_x + cameraX, mouse_y + cameraY);
        }
        if (button == FRMouseButton::RIGHT && !isReleased) {
            abilityUsed = true;
        }

    }

    virtual void onKeyPressed(FRKey k) {
        if (k == FRKey::LEFT) {
            ship->setSpeedX(-10.0);
        } else if (k == FRKey::RIGHT) {
            ship->setSpeedX(10.0);
        }
        if (k == FRKey::UP) {
            ship->setSpeedY(-10.0);
        } else if (k == FRKey::DOWN) {
            ship->setSpeedY(10.0);
        }
    }

    virtual void onKeyReleased(FRKey k) {
        if (k == FRKey::LEFT || k == FRKey::RIGHT) {
            ship->setSpeedX(0.0);
        }
        if (k == FRKey::UP || k == FRKey::DOWN) {
            ship->setSpeedY(0.0);
        }
    }

    virtual const char *GetTitle() override {
        return "asteroids";
    }

};

int main(int argc, char *argv[]) {
    int windowW = SCREEN_WIDTH, windowH = SCREEN_HEIGHT;
    int mapW = MAP_WIDTH, mapH = MAP_HEIGHT;
    int num_ammo = 1, num_asteroids = 30;
    double ability_probability = 0.1;
    string tmp;

    if (argc > 1) {
        for (auto i = 1; i < argc; ++i) {
            if (!strcmp(argv[i], "-window")) {
                tmp = argv[i + 1];
                windowW = stoi(tmp.substr(0, tmp.find('x')));
                windowH = stoi(tmp.substr(tmp.find('x') + 1, tmp.length() - tmp.find('x')));
            } else if (!strcmp(argv[i], "-map")) {
                tmp = argv[i + 1];
                mapW = stoi(tmp.substr(0, tmp.find('x')));
                mapH = stoi(tmp.substr(tmp.find('x') + 1, tmp.length() - tmp.find('x')));
            } else if (!strcmp(argv[i], "-num_asteroids")) {
                num_asteroids = stoi(argv[i + 1]);
            } else if (!strcmp(argv[i], "-num_ammo")) {
                num_ammo = stoi(argv[i + 1]);
            } else if (!strcmp(argv[i], "-ability_probability")) {
                ability_probability = stod(argv[i + 1]);
            }
        }
    }

    if (mapW < windowW)
        mapW = windowW;
    if (mapH < windowH)
        mapH = windowH;

    return run(new MyFramework(windowW, windowH, mapW, mapH, num_ammo, num_asteroids, ability_probability));
}