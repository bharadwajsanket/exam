#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

const int NUM_BRANCHES = 6;

enum class Side { LEFT, RIGHT, NONE };

Sprite branches[NUM_BRANCHES];
Side branchPositions[NUM_BRANCHES];

void updateBranches(int seed)
{
    for (int j = NUM_BRANCHES - 1; j > 0; j--)
        branchPositions[j] = branchPositions[j - 1];

    int r = rand() % 5;

    switch (r)
    {
        case 0: branchPositions[0] = Side::LEFT; break;
        case 1: branchPositions[0] = Side::RIGHT; break;
        default: branchPositions[0] = Side::NONE; break;
    }
}

int main()
{
    srand((int)time(0));

    VideoMode vm(1920,1080);
    RenderWindow window(vm,"Timber Game!!!");

    View view(FloatRect(0,0,1920,1080));
    window.setView(view);

    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    Sprite spriteBackground(textureBackground);

    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree(textureTree);
    spriteTree.setPosition(810,0);

    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    Sprite spriteCloud1(textureCloud);
    Sprite spriteCloud2(textureCloud);
    Sprite spriteCloud3(textureCloud);

    spriteCloud1.setScale(0.6,0.6);
    spriteCloud2.setScale(0.4,0.4);
    spriteCloud3.setScale(0.9,0.9);

    bool cloudActive1=false,cloudActive2=false,cloudActive3=false;
    float cloudSpeed1=0,cloudSpeed2=0,cloudSpeed3=0;

    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog(textureLog);
    spriteLog.setPosition(810,720);

    bool logActive=false;
    float logSpeedX=0;
    float logSpeedY=-1500;

    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer(texturePlayer);
    spritePlayer.setPosition(580,720);

    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe(textureAxe);
    spriteAxe.setPosition(700,830);

    const float AXE_POSITION_LEFT=700;
    const float AXE_POSITION_RIGHT=1075;

    Side playerSide=Side::LEFT;
    bool acceptInput=false;

    Texture textureRip;
    textureRip.loadFromFile("graphics/rip.png");
    Sprite spriteRip(textureRip);
    spriteRip.setPosition(3000,720);

    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    for(int i=0;i<NUM_BRANCHES;i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setOrigin(220,20);
        branchPositions[i]=Side::NONE;
    }

    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);
    branchPositions[5]=Side::NONE;

    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee(textureBee);

    bool beeActive=false;
    float beeSpeed=0;

    // Sounds
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    Sound chopSound(chopBuffer);

    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/death.wav");
    Sound deathSound(deathBuffer);

    SoundBuffer outOfTimeBuffer;
    outOfTimeBuffer.loadFromFile("sound/out_of_time.wav");
    Sound outOfTimeSound(outOfTimeBuffer);

    Font font;
    font.loadFromFile("font/KOMIKAP_.ttf");

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::Red);
    scoreText.setPosition(20,20);

    int score=0;
    int highestScore=0;

    Text highestScoreText;
    highestScoreText.setFont(font);
    highestScoreText.setCharacterSize(50);
    highestScoreText.setFillColor(Color::Yellow);
    highestScoreText.setPosition(20,120);

    Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::Green);
    messageText.setString("Press Enter to Start");

    FloatRect textRect=messageText.getLocalBounds();
    messageText.setOrigin(
        textRect.left+textRect.width/2.0f,
        textRect.top+textRect.height/2.0f);
    messageText.setPosition(1920/2.0f,1080/2.0f);

    RectangleShape timeBar;
    float timeBarStartWidth=400;
    float timeBarHeight=80;

    timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920/2)-timeBarStartWidth/2,980);

    float timeRemaining=6.0f;
    float timeBarWidthPerSecond=timeBarStartWidth/timeRemaining;

    bool paused=true;

    Clock clock;
    Time dt;

    while(window.isOpen())
    {
        dt=clock.restart();

        Event event;
        while(window.pollEvent(event))
        {
            if(event.type==Event::Closed)
                window.close();

            if(event.type==Event::KeyPressed &&
               event.key.code==Keyboard::Enter && paused)
            {
                paused=false;
                timeRemaining=6.0f;
                score=0;
                acceptInput=true;

                messageText.setString("");

                spritePlayer.setPosition(580,720);
                spriteRip.setPosition(3000,720);

                for(int i=0;i<NUM_BRANCHES;i++)
                    branchPositions[i]=Side::NONE;

                updateBranches(1);
                updateBranches(2);
                updateBranches(3);
                updateBranches(4);
                updateBranches(5);
                branchPositions[5]=Side::NONE;
            }

            if(event.type==Event::KeyReleased && !paused)
            {
                acceptInput=true;
                spriteAxe.setPosition(2000,830);
            }
        }

        if(!paused)
        {
            timeRemaining-=dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond*timeRemaining,timeBarHeight));

            if(timeRemaining<=0)
            {
                paused=true;

                if(score>highestScore)
                    highestScore=score;

                messageText.setString("Out of Time!");
                outOfTimeSound.play();
            }

            if(acceptInput)
            {
                if(Keyboard::isKeyPressed(Keyboard::Left))
                {
                    playerSide=Side::LEFT;
                    spritePlayer.setPosition(580,720);
                    spriteAxe.setPosition(AXE_POSITION_LEFT,830);

                    score++;
                    timeRemaining+=(2/score)+.15;

                    updateBranches(score);

                    spriteLog.setPosition(810,720);
                    logSpeedX=5000;
                    logActive=true;

                    acceptInput=false;
                    chopSound.play();
                }

                if(Keyboard::isKeyPressed(Keyboard::Right))
                {
                    playerSide=Side::RIGHT;
                    spritePlayer.setPosition(1200,720);
                    spriteAxe.setPosition(AXE_POSITION_RIGHT,830);

                    score++;
                    timeRemaining+=(2/score)+.15;

                    updateBranches(score);

                    spriteLog.setPosition(810,720);
                    logSpeedX=-5000;
                    logActive=true;

                    acceptInput=false;
                    chopSound.play();
                }
            }

            if(branchPositions[5]==playerSide)
            {
                paused=true;
                acceptInput=false;

                spritePlayer.setPosition(2000,720);

                if(playerSide==Side::LEFT)
                    spriteRip.setPosition(600,720);
                else
                    spriteRip.setPosition(1150,720);

                if(score>highestScore)
                    highestScore=score;

                messageText.setString("SQUISHED!!");
                deathSound.play();
            }

            stringstream ss;
            ss<<"Score = "<<score;
            scoreText.setString(ss.str());

            stringstream hs;
            hs<<"High Score = "<<highestScore;
            highestScoreText.setString(hs.str());
        }

        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteTree);

        for(int i=0;i<NUM_BRANCHES;i++)
            window.draw(branches[i]);

        window.draw(spritePlayer);
        window.draw(spriteRip);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteBee);

        window.draw(scoreText);
        window.draw(highestScoreText);
        window.draw(timeBar);

        if(paused)
            window.draw(messageText);

        window.display();
    }

    return 0;
}
