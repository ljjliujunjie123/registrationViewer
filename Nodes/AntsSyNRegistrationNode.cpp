//
// Created by ZZY on 2021/12/28.
//

#include "AntsSyNRegistrationNode.h"

AntsSyNRegistrationNode::AntsSyNRegistrationNode(string name, string desc) : AbsNode(name, desc) {
    initControls();
}

void AntsSyNRegistrationNode::initControls() {
    ControlWrapper levelsComposite = CompositeControl(1, "Levels", "配置Affine配准的层级<降采样率， 迭代次数，平滑半径>，低层级运算速度快，高层级运算精度高", {
            ControlWrapper(TripleSpinControl(2, "Level 1","",{6,16,8,"Shrink Factor"}, {10, 1000, 1000, "Iterations"}, {3,10,3,"Smooth"})),
            ControlWrapper(TripleSpinControl(3, "Level 2","",{3,8,4,"Shrink Factor"}, {10, 1000, 500, "Iterations"}, {2,4,2,"Smooth"})),
            ControlWrapper(TripleSpinControl(4, "Level 3","",{2,3,2,"Shrink Factor"}, {10, 1000, 250, "Iterations"}, {1,2,1,"Smooth"})),
            ControlWrapper(TripleSpinControl(5, "Level 4","",{1,2,1,"Shrink Factor"}, {10, 1000, 100, "Iterations"}, {0,1,0,"Smooth"}))
    });

    MultiTypeControl metrics = MultiTypeControl(6, "Metric", "选择一种Metric", {
            {"CC", {
                           ControlWrapper(SpinBoxControl<int>(7, "Radius", "Cross Correlation Metric, Radius of sampling", {1, 10},4)),
                           ControlWrapper(ComboBoxControl(8, "Sampling Strategy", "Choose a Strategy for choosing sampling points",{"None", "Regular", "Random"}, "None")),
                           ControlWrapper(SliderControl(9, "Sampling Percentage", "", {0, 100}, 0))
                   }},
            {"MI", {
                           ControlWrapper(SpinBoxControl<int>(10, "Number of Bins", "Mutual Information Metric, Histogram Bins", {8, 64},32)),
                           ControlWrapper(ComboBoxControl(11, "Sampling Strategy", "Choose a Strategy for choosing sampling points",{"None", "Regular", "Random"}, "Regular")),
                           ControlWrapper(SliderControl(12, "Sampling Percentage", "", {0, 100}, 25))
                   }},
            {"Mattes", {
                           ControlWrapper(SpinBoxControl<int>(13, "Number of Bins", "Mattes Metric, Histogram Bins", {8, 64},32)),
                           ControlWrapper(ComboBoxControl(14, "Sampling Strategy", "Choose a Strategy for choosing sampling points",{"None", "Regular", "Random"}, "Regular")),
                           ControlWrapper(SliderControl(15, "Sampling Percentage", "", {0, 100}, 25))
                   }},
            {"Demons", {
                           ControlWrapper(ComboBoxControl(16, "Sampling Strategy", "Choose a Strategy for choosing sampling points",{"None", "Regular", "Random"}, "Regular")),
                           ControlWrapper(SliderControl(17, "Sampling Percentage", "", {0, 100}, 25))
                   }}
    }, "CC");
    controls = {
            ControlWrapper(SpinBoxControl<float>(18, "Gradient Step", "优化梯度步长", {0.0, 1.0}, 0.1)),
            ControlWrapper(SpinBoxControl<float>(19, "updateFieldVarianceInVoxelSpace", "", {1.0,5.0}, 3.0)),
            ControlWrapper(SpinBoxControl<float>(20, "totalFieldVarianceInVoxelSpace", "", {0.0, 1.0}, 0.0, false)),
            levelsComposite,
            metrics
    };
}
