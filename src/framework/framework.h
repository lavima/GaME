#pragma once

namespace game::framework {

    enum class GAME_API GameStatus {
        Created = 0,
        Initialized,
        Running,
        Paused,
        Terminated
    };

    enum class GAME_API GameLoopStage {
        PreGameUpdate,
        PostGameUpdate
    };

}
