#ifndef THREATSOBJECT_H_INCLUDED
#define THREATSOBJECT_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObject.h"

class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

    void set_x_val_threats(const int& xVal){x_val_threats = xVal;}
    void set_y_val_threats(const int& yVal){y_val_threats = yVal;}
    int get_x_val_threats() const {return x_val_threats;}
    int get_y_val_threats() const {return y_val_threats;}

    void set_is_move_threats(const bool& isMove){is_move_threats = isMove;}
    bool get_is_move_threats() const {return is_move_threats;}

    void HandleMoveThreats(const int& x_border, const int& y_border);

private:
    int x_val_threats;
    int y_val_threats;
    bool is_move_threats;
};


#endif // THREATSOBJECT_H_INCLUDED
