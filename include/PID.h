#ifndef PID_H
#define PID_H

class PID
{
public:

    PID();

    float compute(
        int error
    );

    void reset();

private:

    float integral;

    int derivative;

    int lastError;
};

#endif