#ifndef _NN_DEMO_H_
#define _NN_DEMO_H_

#include "MyNetDCNN/MyNetDCNN.h"

class NNDemo
{
  private:
    unsigned int item_idx;
    unsigned int nn_result, correct, wrong, duration;

    MyNetDCNN nn;

  public:
    NNDemo();
    virtual ~NNDemo();

    void main();

  private:
    void show_dataset_item(unsigned int idx);
    void show_result();


  private:
    unsigned char* get_dataset_item(unsigned int idx);
    void network_set_input(unsigned int idx);

};

#endif
