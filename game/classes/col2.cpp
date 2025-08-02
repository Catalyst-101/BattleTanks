#include "PlayerTank.h"
#include "EnemyTank1.h"

bool PlayerTank::checkBulletCollisions(EnemyTank1& enemy) 
{
    for (auto it = bulletVec.begin(); it != bulletVec.end(); ++it) 
    {
        if (it->getBounds().intersects(enemy.getTankBounds())) 
        {
            enemy.resetPosition();
            it = bulletVec.erase(it); // Remove the bullet
            return true;
        }
    }
    return false;
}

bool EnemyTank1::bulletCollision(PlayerTank& player) 
{
    for (auto it = bulletVec.begin(); it != bulletVec.end(); ++it) 
    {
        if (it->getBounds().intersects(player.getTankBounds())) 
        {
            cout << "Player Died!" << endl;
            player.resetPosition();
            it = bulletVec.erase(it); // Remove the bullet
            return true;
        }
    }

    // Check collision between the enemy tank itself and the player
    if (enemyTank.getGlobalBounds().intersects(player.getTankBounds())) 
    {
        resetPosition();
        cout << "Player Died!" << endl;
        player.resetPosition();
        return true;
    }

    return false;
}
