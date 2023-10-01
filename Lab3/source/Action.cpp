#include "Action.H"

Action::Action()
{
	action = 0;
}

bool Action::IsUp()    { return action == 1; }
bool Action::IsRight() { return action == 2; }
bool Action::IsDown()  { return action == 3; }
bool Action::IsLeft()  { return action == 4; }
bool Action::IsOpen()  { return action == 5; }
bool Action::IsEmpty()  { return action == 0; }
void Action::SetUp()    { action = 1; } 
void Action::SetRight() { action = 2; }
void Action::SetDown()  { action = 3; }
void Action::SetLeft()  { action = 4; }
void Action::SetOpen()  { action = 5; }

std::string Action::GetText()
{
    if      (IsUp())    return "UP";
    else if (IsRight()) return "RIGHT";
    else if (IsDown())  return "DOWN";
    else if (IsLeft())  return "LEFT";
    else if (IsOpen())  return "OPEN";
    return "";
}

