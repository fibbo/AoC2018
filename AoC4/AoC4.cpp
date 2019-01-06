#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

#include "Definitions.h"

enum class
    Type {
    Start,
    Asleep,
    WakeUp,
    Unknown,
};


Type getType(std::string s)
{
    if (s == "Guard") return Type::Start;
    if (s == "falls") return Type::Asleep;
    if (s == "wakes") return Type::WakeUp;
    return Type::Unknown;
}

using EntryPtr = std::shared_ptr<Entry>;

void strategy1(std::map<int, Guard*> guards)
{
    int minutes_asleep = 0;
    Guard* sleepyHead = nullptr;
    for (auto kv : guards)
    {
        if (kv.second->minutes_asleep > minutes_asleep)
        {
            sleepyHead = kv.second;
            minutes_asleep = kv.second->minutes_asleep;
        }
    }

    int minutes[60] = { 0 };

    for (auto par : sleepyHead->phases)
    {
        for (int i = par.first; i < par.second; i++)
        {
            ++minutes[i];
        }
    }

    int best_minute = 0;
    int index = 0;
    for (int i = 0; i < 60; i++)
    {
        if (minutes[i] > best_minute)
        {
            best_minute = minutes[i];
            index = i;
        }
    }

    std::cout << sleepyHead->id * index << '\n';
}

void strategy2(std::map<int, Guard*> guards)
{

    
    int best_minute = 0;
    int index = 0;
    int id = 0;
    for (const auto kv : guards)
    {
        int minutes[60] = { 0 };
        for (auto par : kv.second->phases)
        {
            for (int i = par.first; i < par.second; i++)
            {
                ++minutes[i];
            }
        }
        for (int i = 0; i < 60; i++)
        {
            if (minutes[i] > best_minute)
            {
                best_minute = minutes[i];
                index = i;
                id = kv.second->id;
            }
        }
        
    }
    std::cout << id * index << '\n';
}

int main()
{
    std::ifstream file("4.txt");
    std::string line;
    std::vector<std::shared_ptr<Entry>> log;

    while (std::getline(file, line))
    {
        Entry entry;
        entry.date = Date(std::string(&line[1], &line[17]));
        entry.message = std::string(line.begin()+19, line.end());
        log.push_back(std::make_shared<Entry>(entry));
    }

    std::sort(log.begin(), log.end(), 
        [](const EntryPtr l, const EntryPtr r) {
        return *l < *r; 
    });

    std::ofstream sorted_log("sorted4.txt");
    for (auto entry : log)
    {
        sorted_log << entry->date << " " << entry->message << '\n';
    }
    sorted_log.close();

    auto it = log.begin();
    Guard* guard = nullptr;
    std::map<int, Guard*> guards;
    int sleep;
    while (it != log.end())
    {
        auto split_line = split((*it)->message, ' ');
        switch (getType(split_line[0]))
        {
        case Type::Start:
        {
        if (guard != nullptr) guards.insert(std::make_pair(guard->id, guard));
        int id = std::stoi(std::string(split_line[1].begin() + 1, split_line[1].end()));
        auto t_it = guards.find(id);
        if (t_it != guards.end())
            guard = guards.at(id);
        else
        {
            guard = new Guard;
            guard->id = id;
        }
            
        break;
        }
        case Type::Asleep:
            sleep = (*it)->date.minute;
            break;
        case Type::WakeUp:
        {
        int sleep_time = (*it)->date.minute - sleep;
        guard->minutes_asleep += sleep_time;
        guard->phases.push_back(std::make_pair(sleep, (*it)->date.minute ));

        break;
        }
        default:
            std::cout << "Unknown type: " << split_line[0] << '\n';
            break;
        }
        ++it;
    }

    strategy1(guards);

    strategy2(guards);

    std::getchar();
    return 0;
}

