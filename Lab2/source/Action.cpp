#include "Action.H"

Action::Action()
{
	action = 0;
}

bool Action::IsUp()    { return action == 1; }
bool Action::IsRight() { return action == 2; }
bool Action::IsDown()  { return action == 3; }
bool Action::IsLeft()  { return action == 4; }

void Action::SetUp()    { action = 1; } 
void Action::SetRight() { action = 2; }
void Action::SetDown()  { action = 3; }
void Action::SetLeft()  { action = 4; }
