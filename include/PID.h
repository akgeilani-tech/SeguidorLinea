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

    float derivative;

    float derivativeFiltered;

    float lastError;
};

#endif