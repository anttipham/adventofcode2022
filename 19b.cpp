#include <bits/stdc++.h>
using namespace std;

struct Materials {
    int ore = 0;
    int clay = 0;
    int obsidian = 0;
    int geode = 0;

    bool operator>=(Materials const& other) const {
        return ore >= other.ore &&
               clay >= other.clay &&
               obsidian >= other.obsidian &&
               geode >= other.geode;
    }

    Materials& operator+=(Materials const& other) {
        ore += other.ore;
        clay += other.clay;
        obsidian += other.obsidian;
        geode += other.geode;
        return *this;
    }

    Materials& operator-=(Materials const& other) {
        ore -= other.ore;
        clay -= other.clay;
        obsidian -= other.obsidian;
        geode -= other.geode;
        return *this;
    }
};
struct Blueprint {
    Materials oreRobotCost;
    Materials clayRobotCost;
    Materials obsidianRobotCost;
    Materials geodeRobotCost;
    Blueprint(int ore, int clay, int obsidianOre, int obsidianClay, int geodeOre, int geodeObsidian)
        : oreRobotCost({ ore: ore })
        , clayRobotCost ({ ore: clay })
        , obsidianRobotCost ({ ore: obsidianOre, clay: obsidianClay })
        , geodeRobotCost ({ ore: geodeOre, obsidian: geodeObsidian }) {}
};
int const T = 32;

/**
 * @brief https://www.reddit.com/r/adventofcode/comments/zpihwi/comment/j0tls7a/?utm_source=share&utm_medium=web2x&context=3
 *
 * 1. Branch on selecting a type of robot to build as a goal, then iterate until
 * we have the resources.
 *
 * 2. If we don't have any clay robots, we can't try to build an obsidian robot.
 * And if we don't have any obsidian robots, we can't try to build a geode
 * robots.
 *
 * 3. Don't build any more ore, clay, or obsidian robots than needed.
 *
 * 4. The upper bound on the number of geodes we can hit in the time remaining is
 * the current count so far, plus the number the current set of robots could
 * collect in the remaining time, plus a quadratic sequence assuming we could
 * optimistically build a geode robot every minute. Prune the branch if that's
 * less than the best solution found so far.
 *
 * @return int Number of geodes
 */
int dfs_geode(Materials const& materials, Blueprint const& blueprint, Materials const& robots, int& bestgeode, int const time) {
    if (time == T) return materials.geode;

    int timeleft = T - time;
    int theoretical_maxgeode = materials.geode + timeleft * (robots.geode + robots.geode + timeleft) / 2;
    if (theoretical_maxgeode <= bestgeode) return 0;

    int maxobsidianrobot = blueprint.geodeRobotCost.obsidian;
    int maxclayrobot = blueprint.obsidianRobotCost.clay;
    int maxorerobot = max(blueprint.geodeRobotCost.ore, blueprint.obsidianRobotCost.ore);
    maxorerobot = max(maxorerobot, blueprint.clayRobotCost.ore);

    int maxgeode = 0;
    // Build geode robot
    if (robots.obsidian) {
        Materials robots_ = robots;
        Materials materials_ = materials;
        int time_ = time;
        while (time_ < T && !(materials_ >= blueprint.geodeRobotCost)) {
            materials_ += robots;
            time_++;
        }
        if (time_ < T) {
            materials_ -= blueprint.geodeRobotCost;
            materials_ += robots;
            time_++;
            robots_.geode++;
        }
        maxgeode = max(maxgeode, dfs_geode(materials_, blueprint, robots_, bestgeode, time_));
        bestgeode = max(bestgeode, maxgeode);
    }
    // Build obsidian robot
    if (robots.clay && robots.obsidian <= maxobsidianrobot) {
        Materials robots_ = robots;
        Materials materials_ = materials;
        int time_ = time;
        while (time_ < T && !(materials_ >= blueprint.obsidianRobotCost)) {
            materials_ += robots;
            time_++;
        }
        if (time_ < T) {
            materials_ -= blueprint.obsidianRobotCost;
            materials_ += robots;
            time_++;
            robots_.obsidian++;
        }
        maxgeode = max(maxgeode, dfs_geode(materials_, blueprint, robots_, bestgeode, time_));
        bestgeode = max(bestgeode, maxgeode);
    }
    // Build clay robot
    if (robots.clay <= maxclayrobot) {
        Materials robots_ = robots;
        Materials materials_ = materials;
        int time_ = time;
        while (time_ < T && !(materials_ >= blueprint.clayRobotCost)) {
            materials_ += robots;
            time_++;
        }
        if (time_ < T) {
            materials_ -= blueprint.clayRobotCost;
            materials_ += robots;
            time_++;
            robots_.clay++;
        }
        maxgeode = max(maxgeode, dfs_geode(materials_, blueprint, robots_, bestgeode, time_));
        bestgeode = max(bestgeode, maxgeode);
    }
    // Build ore robot
    if (robots.ore <= maxorerobot) {
        Materials robots_ = robots;
        Materials materials_ = materials;
        int time_ = time;
        while (time_ < T && !(materials_ >= blueprint.oreRobotCost)) {
            materials_ += robots;
            time_++;
        }
        if (time_ < T) {
            materials_ -= blueprint.oreRobotCost;
            materials_ += robots;
            time_++;
            robots_.ore++;
        }
        maxgeode = max(maxgeode, dfs_geode(materials_, blueprint, robots_, bestgeode, time_));
        bestgeode = max(bestgeode, maxgeode);
    }
    return maxgeode;
}

int main() {
    vector<Blueprint> blueprints;
    int index_, ore_, clay_, obsidianOre_, obsidianClay_, geodeOre_, geodeObsidian_;
    while (scanf(" Blueprint %d: "
                 "Each ore robot costs %d ore. "
                 "Each clay robot costs %d ore. "
                 "Each obsidian robot costs %d ore and %d clay. "
                 "Each geode robot costs %d ore and %d obsidian.",
                 &index_, &ore_, &clay_, &obsidianOre_, &obsidianClay_, &geodeOre_, &geodeObsidian_) > 0) {
        blueprints.emplace_back(ore_, clay_, obsidianOre_, obsidianClay_, geodeOre_, geodeObsidian_);
    }
    int res = 1;
    for (int i = 0; i < 3; i++) {
        int bestgeode = 0;
        int geode = dfs_geode({}, blueprints[i], { ore: 1 }, bestgeode, 0);
        cout << "i " << i << ": " << geode << endl;
        res *= geode;
    }
    cout << res << endl;
}
