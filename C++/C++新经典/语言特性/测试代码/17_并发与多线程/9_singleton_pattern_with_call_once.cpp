#include <mutex>

using namespace std;

class GameConfig
{
private:
    GameConfig() {}
    GameConfig(const GameConfig&) {}
    GameConfig& operator=(const GameConfig&) {}
    ~GameConfig() {}

    static void createInstance()
    {
        if (!m_instance)
        {
            m_instance = new GameConfig();
        }
    }
public:
    static GameConfig* getInstance()
    {
        if (!m_instance)
        {
            call_once(m_flag_creation, createInstance);
        }
        return m_instance;
    }

private:
    static GameConfig*  m_instance;
    static once_flag    m_flag_creation;
};

GameConfig* GameConfig::m_instance = nullptr;