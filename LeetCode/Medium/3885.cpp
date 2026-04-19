struct Event {
    int eventId, priority;
};

struct EventComparator {
    bool operator()(const Event &e1, const Event &e2) {
        if (e1.priority != e2.priority) {
            return e1.priority < e2.priority;
        } else {
            return e1.eventId > e2.eventId;
        }
    }
};

class EventManager {
    priority_queue<Event, vector<Event>, EventComparator> events;
    unordered_map<int, int> priorities;

public:
    EventManager(vector<vector<int>>& events) {
        for (int i = 0; i < events.size(); ++i) {
            int eventId = events[i][0], priority = events[i][1];
            this->events.push(Event{eventId, priority});
            priorities[eventId] = priority;
        }
    }
    
    void updatePriority(int eventId, int newPriority) {
        if (priorities[eventId] == newPriority) return;

        priorities[eventId] = newPriority;
        events.push(Event{eventId, newPriority});
    }
    
    int pollHighest() {
        while (events.size()) {
            Event event = events.top();
            events.pop();
            if (
                priorities.count(event.eventId) &&
                priorities[event.eventId] == event.priority
            ) {
                priorities.erase(event.eventId);
                return event.eventId;
            }
        }
        return -1;
    }
};

/**
 * Your EventManager object will be instantiated and called as such:
 * EventManager* obj = new EventManager(events);
 * obj->updatePriority(eventId,newPriority);
 * int param_2 = obj->pollHighest();
 */
