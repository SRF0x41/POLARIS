#include <torch/torch.h>
#include <iostream>
#include "NeuralNet.cpp"

using namespace torch;

class ProtoLimbic{
    private:
    Tensor internal_target;


    public:
    ProtoLimbic(){

    }

    ProtoLimbic(NeuralNet neural_net){
        int n_out = neural_net.getOutputSize();
        internal_target = rand({n_out});
    }

    Tensor internalTarget(){
        return internal_target;
    }

}