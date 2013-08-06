
/*##########################
  ######## DHkeygen ########
  ##########################
*/

#ifndef DHkeygen_h
#define DHkeygen_h

#include "Arduino.h"
#include "Utility/Entropy.h"

class DHkeygen
{
  private:
    unsigned long _random_int;// stores the random integer
    const int _p= 524287;// large prime :P -  Selected?
    const int _a=7;// DH alpha parameter
    unsigned long _xa[2];// stored the random genrated value (private)
    double _k[2], /* _t_k, */ _ya[2], _yb[2];
    //uint8_t *_key1[16];
    
    unsigned long calc_y(unsigned long b, unsigned long e, unsigned long m); //Base expoential mod function calculation
    
    unsigned long randum(); //Uses the Entropy library to generate random numbers
    void randgen(); //Calls two instances of randum()
    
    void publickey_calc(); //container to call calculation_y twice to calculate own public key
    unsigned long calculation_y(unsigned long x); //DH algorithm routine
    
    double genpart(double y, unsigned long x);//was calc_k - called to generate key whenever other's public or our own private values varies
    
  public:
    DHkeygen();
    void DH_Pub(); //calculates the node's public key
    
    void genkey(void* data); //generates the common secret key when given other's public key
    
    void formatkey(uint8_t *key);//was set_key - converts the key to the format required by the AES algorithm. Called automatically by the genkey function
};

#endif
