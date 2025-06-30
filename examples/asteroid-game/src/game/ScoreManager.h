//
// Created by artem on 27.06.24.
//

#ifndef ENGINE_SCOREMANAGER_H
#define ENGINE_SCOREMANAGER_H


#include <Engine.h>

class ScoreManager {
public:
    ScoreManager() : score(0) {

    }

    void addPoints(int points) {
        score += points;
        ServiceProvider::get<EventDispatcher>()->dispatch(EventDispatcher::EVENT_SCORE_REACHED, nullptr);
    }

    void subPoints(int points){
        score -= points;
    }

    int getScore() const {
        return score;
    }

    void resetScore() {
        score = 0;
    }

private:
    int score;
};

#endif //ENGINE_SCOREMANAGER_H
