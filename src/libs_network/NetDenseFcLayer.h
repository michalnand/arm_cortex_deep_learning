#ifndef _NetDense_Layer_H_
#define _NetDense_Layer_H_

#include "NetworkLayer.h"

class NetDenseFcLayer: public NetworkLayer
{
  private:
    const nn_weight_t  *m_weights, *m_bias;
    nn_t   m_weights_range, m_bias_range;

    unsigned int m_outputs_count, m_neurons_count, m_inputs_count;

  public:
    NetDenseFcLayer(
                sLayerGeometry kernel_geometry,
                sLayerGeometry input_geometry,
                sLayerGeometry output_geometry,

                const nn_weight_t *weights,
                const nn_weight_t *bias,
                int weights_range,
                int bias_range
              );

    virtual ~NetDenseFcLayer();

    void forward(nn_layer_t *output, nn_layer_t *input);
};

#endif
