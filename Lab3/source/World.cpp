#include "World.H"

World::World() {}

int  World::GetStartRoom()   { return 1;         }
bool World::IsExit(int room) { return room == 11;}

// Returns a list of actions that can be played in each particular room
list<Action> World::GetActionsForRoom(int room, bool open_action)
{
    std::list<Action> l_actions;

    if (room == 1 || room == 3 || room == 6)
    {
        Action up;    up.SetUp();
        Action right; right.SetRight();
        Action down;  down.SetDown();
        Action left;  left.SetLeft();
        l_actions.push_back(up);
        l_actions.push_back(right);
        l_actions.push_back(down);
        l_actions.push_back(left);
    }
    else if (room == 2)
    {
        Action right; right.SetRight();
        Action down;  down.SetDown();
        Action left;  left.SetLeft();
        l_actions.push_back(right);
        l_actions.push_back(down);
        l_actions.push_back(left);
    }
    else if (room == 4)
    {
        Action up;    up.SetUp();
        Action right; right.SetRight();
        Action left;  left.SetLeft();
        l_actions.push_back(up);
        l_actions.push_back(right);
        l_actions.push_back(left);
    }
    else if (room == 5)
    {
        Action right; right.SetRight();
        Action down;  down.SetDown();
        Action left;  left.SetLeft();
        l_actions.push_back(right);
        l_actions.push_back(down);
        l_actions.push_back(left);

        if (open_action)
        {
            Action open;  open.SetOpen();
            l_actions.push_back(open);
        }
    }
    else if (room == 7)
    {
        Action up;    up.SetUp();
        Action down;  down.SetDown();
        Action left;  left.SetLeft();
        l_actions.push_back(up);
        l_actions.push_back(down);
        l_actions.push_back(left);

        if (open_action)
        {
            Action open;  open.SetOpen();
            l_actions.push_back(open);
        }
    }
    else if (room == 8)
    {
        Action up;    up.SetUp();
        Action right; right.SetRight();
        Action down;  down.SetDown();
        Action left;  left.SetLeft();
        l_actions.push_back(up);
        l_actions.push_back(right);
        l_actions.push_back(down);
        l_actions.push_back(left);
        if (open_action)
        {
            Action open; open.SetOpen();
            l_actions.push_back(open);
        }
    }
    else if (room == 9)
    {
        Action up;    up.SetUp();
        Action right; right.SetRight();
        Action left;  left.SetLeft();
        l_actions.push_back(up);
        l_actions.push_back(right);
        l_actions.push_back(left);
    }
    else if (room == 10)
    {
        Action right; right.SetRight();
        Action left;  left.SetLeft();
        l_actions.push_back(right);
        l_actions.push_back(left);
    }
    else if (room == 12)
    {
        Action right; right.SetRight();
        Action left;  left.SetLeft();
        l_actions.push_back(right);
        l_actions.push_back(left);
    }
    else if (room == 13)
    {
        Action right; right.SetRight();
        Action left;  left.SetLeft();
        l_actions.push_back(right);
        l_actions.push_back(left);
    }

    return l_actions;
}

// Return a string with the text for each room
string World::GetTextForRoom(int room)
{
    if (room == 1)       { return "It's an empty offce room.";  }
    else if (room == 2)  { return "It's at a turn.";  }
    else if (room == 3)  { return "It seems rather empty.";  }
    else if (room == 4)  { return "It's a corridor split.";  }
    else if (room == 5)  { return "It isn't as boring.";  }
    else if (room == 6)  { return "It's an intersection.";  }
    else if (room == 7)  { return "There's a couple desks.";  }
    else if (room == 8)  { return "It seems different";  }
    else if (room == 9)  { return "There's an open door.";  }
    else if (room == 10) { return "It seems pretty mudane."; }
    else if (room == 11) { return "You've found the exit!"; }
    else if (room == 12) { return "It seems quite weird."; }
    else if (room == 13) { return "It's an empty corridor."; }
    return "";
}

