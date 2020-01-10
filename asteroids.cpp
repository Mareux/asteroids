

#include "game.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define MAP_WIDTH 2000
#define MAP_HEIGHT 2000

using namespace std;

double dot(double a_x, double a_y, double b_x, double b_y){
    return (a_x * b_x) + (a_y * b_y);
}

double perpDot(double a_x, double a_y, double b_x, double b_y){
    return (a_y * b_x) - (a_x * b_y);
}

double    random_between_two_int(double min, double max){
    return (min + 1) + (((double) rand()) / (double) RAND_MAX) * (max - (min + 1));
}

int randomInt(int outerMin, int outerMax, int innerMin, int innerMax){
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
    Sprite *abilitySprite;

    vector<Asteroid> bigAsteroids;
    vector<Asteroid> asteroids;
    vector<Asteroid> Asteroids;
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

    bool abilityUsed = false;

    Asteroid addSmallAsteroid(){
        Asteroid asteroid = Asteroid(false);
        asteroid.setObjectSize(widthSmall, heightSmall);
        return asteroid;
    }

    Asteroid addBigAsteroid(){
        Asteroid asteroid = Asteroid(true);
        asteroid.setObjectSize(widthBig, heightBig);
        return asteroid;
    }

    vector<Asteroid> createAsteroids(int asteroidQuantity) {
        vector<Asteroid> asteroid;

        int width, height;

        cout << asteroidQuantity << endl;

        for (auto i = 0; i < asteroidQuantity; ++i){
            bool big = rand() % 2;

            if (big) {
                asteroid.emplace_back(addBigAsteroid());
            }
            else
                asteroid.emplace_back(addSmallAsteroid());
            asteroid.at(i).setPositionX(randomInt(0, MAP_WIDTH, SCREEN_WIDTH / 2 - 50, SCREEN_WIDTH / 2 + 50));
            asteroid.at(i).setPositionY(randomInt(0, MAP_HEIGHT, SCREEN_HEIGHT / 2 - 50, SCREEN_HEIGHT / 2 + 50));

            asteroid.at(i).setDirection(random_between_two_int(-2, 1), random_between_two_int(-2, 1));

            asteroid.at(i).setSpeed(random_between_two_int(0, 4));
        }

        return asteroid;

    }

    void specialAbulity(){

    }

    void dealWithBulletCollision(){
        std::__wrap_iter<Asteroid*> asteroidPos;

        if (ship->checkBulletCollision(asteroids, asteroidPos)) {
            double x = asteroidPos->getLeftUpX();
            double y = asteroidPos->getLeftUpY();

            if (asteroidPos->isBig()){

                asteroids.erase(asteroidPos);

                cout<< "shoot!";
                asteroids.emplace_back(addSmallAsteroid());
                auto asteroid = asteroids.size() - 1;
                asteroids.at(asteroid).setPositionY(y - 20);
                asteroids.at(asteroid).setPositionX(x - 20);
                asteroids.at(asteroid).setDirection(-1, -1);
                asteroids.at(asteroid).setSpeed(5);

                asteroids.emplace_back(addSmallAsteroid());
                asteroid = asteroids.size() - 1;
                asteroids.at(asteroid).setPositionY(y + 20);
                asteroids.at(asteroid).setPositionX(x + 20);
                asteroids.at(asteroid).setDirection(1, 1);
                asteroids.at(asteroid).setSpeed(5);

            }
            else {
                asteroids.erase(asteroidPos);
            }

            if (rand() % 100 < 100){
                ship->createAbility(x, y, 20, 20);
            }

        }
    }


    void moveCamera() {

        ship->applyVelocity(cameraX, cameraY);

        if (ship->getRightDownX() - cameraX < 0)
            cameraX = MAP_WIDTH - SCREEN_WIDTH;
        else if (ship->getLeftUpX() - cameraX > SCREEN_WIDTH)
            cameraX = 0;
        if (ship->getRightDownY() - cameraY < 0)
            cameraY = MAP_HEIGHT - SCREEN_HEIGHT;
        else if (ship->getLeftUpY() - cameraY > SCREEN_HEIGHT)
            cameraY = 0;   

        if (cameraX < 0 || ceil(ship->getRightDownX() - cameraX) < SCREEN_WIDTH/2.0 - 1.0) {
            cameraX = 0;
        }
        else if (cameraX + SCREEN_WIDTH > MAP_WIDTH ||  ceil(ship->getLeftUpX() - cameraX) > SCREEN_WIDTH/2.0 + 1){
            cameraX = MAP_WIDTH - SCREEN_WIDTH;
        }
        if (cameraY < 0 || ceil(ship->getRightDownY() - cameraY) < SCREEN_HEIGHT/2.0 - 1.0) {
            cameraY = 0;
        }
        else if (cameraY + SCREEN_HEIGHT > MAP_HEIGHT ||  ceil(ship->getLeftUpY() - cameraY) > SCREEN_HEIGHT/2.0 + 1){
            cameraY = MAP_HEIGHT - SCREEN_HEIGHT;
        }
    }//refactor

    static void moveAsteroids(vector<Asteroid> &asteroid, Sprite *asteroidSprite, int screen_w, int screen_h) {

        for(auto & iter : asteroid){
            iter.getObjectFromUnderworld(screen_w, screen_h);
            iter.movement();
        }
    }

    static Ship* createShip(Sprite *shipSprite)
    {
        int width, height;

        getSpriteSize(shipSprite, width, height);
        Ship *ship = new Ship(SCREEN_WIDTH/2.0, SCREEN_HEIGHT/2.0, 0.0, 0,0, width, height, 3);
        return ship;
    }

    static void splitUpAsteroids(Asteroid &firstAsteroid, Asteroid &secondAsteroid) {
        int left = std::max(firstAsteroid.getLeftUpX(), secondAsteroid.getLeftUpX());
        int top = std::max(firstAsteroid.getLeftUpY(), secondAsteroid.getLeftUpY());
        int right = std::min(firstAsteroid.getRightDownX(), secondAsteroid.getRightDownX());
        int bottom = std::min(firstAsteroid.getRightDownY(), secondAsteroid.getRightDownY());

        int width = right - left;
        int height = top - bottom;

        double tmpDirX = firstAsteroid.getDirectionX();
        double tmpDirY = firstAsteroid.getDirectionY();
        double tmpSpeed = firstAsteroid.getSpeed();

        firstAsteroid.setDirection(secondAsteroid.getDirectionX(), secondAsteroid.getDirectionY());
        firstAsteroid.setSpeed(secondAsteroid.getSpeed());
        secondAsteroid.setDirection(tmpDirX, tmpDirY);
        secondAsteroid.setSpeed(tmpSpeed);
    }

    static void asteroidsCollision(vector<Asteroid> &asteroid) {
        for (auto firstIter = 0; firstIter < asteroid.size(); ++ firstIter){
            for (auto secondIter = firstIter + 1; secondIter < asteroid.size(); ++secondIter) {
                if (asteroid[firstIter].collision(asteroid[secondIter].getLeftUpX(),
                        asteroid[secondIter].getLeftUpY(), asteroid[secondIter].getWidth(), asteroid[secondIter].getHeight())) {
                    splitUpAsteroids(asteroid[firstIter], asteroid[secondIter]);
                }
            }
        }
    }


public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = SCREEN_WIDTH;
		height = SCREEN_HEIGHT;
		fullscreen = false;
	}

	virtual bool Init() {

        srand(time(0));

        bigAsteroid = createSprite("data/big_asteroid.png");
        getSpriteSize(bigAsteroid, widthBig, heightBig);
        smallAsteroid = createSprite("data/small_asteroid.png");
        getSpriteSize(smallAsteroid, widthSmall, heightSmall);
        shipSprite = createSprite("data/spaceship.png");
        bulletSprite = createSprite("data/bullet.png");
        abilitySprite = createSprite("data/autoshoot.png");


        asteroids = createAsteroids(30);
        ship = createShip(shipSprite);
        return true;
	}

	virtual void Close() {
        system("leaks Project2");
    }

	virtual bool Tick() {
//		drawTestBackground();

        currentFrameTime = getTickCount();

        if ((currentFrameTime - lastFrameTime) >= FRAME_CONTROL) {
            lastFrameTime = currentFrameTime;

            moveCamera();
            ship->shipMovement();


            asteroidsCollision(asteroids);

            moveAsteroids(asteroids, smallAsteroid, MAP_WIDTH, MAP_HEIGHT);
            ship->moveBullet(MAP_WIDTH, MAP_HEIGHT);
            dealWithBulletCollision();
            ship->getObjectFromUnderworld(MAP_WIDTH, MAP_HEIGHT);

            ship->getAbility();
            if(abilityUsed) {
                ship->useAbility(asteroids, 0, 0);
                abilityUsed = false;
            }


        }
        for (auto & asteroid : asteroids) {
            if (asteroid.isBig())
                drawSprite(bigAsteroid, asteroid.getScreenX() - cameraX, asteroid.getScreenY() - cameraY);
            else
                drawSprite(smallAsteroid, asteroid.getScreenX() - cameraX, asteroid.getScreenY() - cameraY);
        }
        ship->drawAbility(abilitySprite, cameraX, cameraY);
        drawSprite(shipSprite, ship->getScreenX() - cameraX, ship->getScreenY() - cameraY);
        ship->drawBullet(bulletSprite, cameraX, cameraY);
        return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
        mouse_x = x + cameraX;
        mouse_y = y + cameraY;
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
        if (button == FRMouseButton::LEFT && !isReleased)
        {
            ship->createBullet(mouse_x, mouse_y);
            cout<< mouse_x << " : " << mouse_y << endl;
        }
        if (button == FRMouseButton::RIGHT && !isReleased)
        {
            abilityUsed = true;
        }

	}

	virtual void onKeyPressed(FRKey k) {
        if (k == FRKey::LEFT){
            ship->setSpeedX(-10.0);
        }
        else if (k == FRKey::RIGHT){
            ship->setSpeedX(10.0);
        }
        if (k == FRKey::UP){
            ship->setSpeedY(-10.0);
        }
        else if (k == FRKey::DOWN){
            ship->setSpeedY(10.0);
        }
    }

	virtual void onKeyReleased(FRKey k) {
        if (k == FRKey::LEFT || k == FRKey::RIGHT){
            ship->setSpeedX(0.0);
        }
        if (k == FRKey::UP || k == FRKey::DOWN){
            ship->setSpeedY(0.0);
        }
	}

	virtual const char* GetTitle() override
	{
		return "asteroids";
	}

};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}