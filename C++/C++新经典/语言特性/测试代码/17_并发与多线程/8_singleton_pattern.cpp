class GameConfig
{
private:
    GameConfig() {}
    GameConfig(const GameConfig&) {}
    GameConfig& operator=(const GameConfig&) {}
    ~GameConfig() {}
public:
    static GameConfig* getInstance()
    {
        if (!m_instance)
        {
            m_instance = new GameConfig();
        }
        return m_instance;
    }

private:
    static GameConfig* m_instance;
};

GameConfig* GameConfig::m_instance = nullptr;