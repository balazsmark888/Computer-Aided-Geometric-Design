#include "MainWindow.h"

namespace cagd
{
    MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    {
        setupUi(this);

    /*

      the structure of the main window's central widget

     *---------------------------------------------------*
     |                 central widget                    |
     |                                                   |
     |  *---------------------------*-----------------*  |
     |  |     rendering context     |   scroll area   |  |
     |  |       OpenGL widget       | *-------------* |  |
     |  |                           | | side widget | |  |
     |  |                           | |             | |  |
     |  |                           | |             | |  |
     |  |                           | *-------------* |  |
     |  *---------------------------*-----------------*  |
     |                                                   |
     *---------------------------------------------------*

    */
        _side_widget = new SideWidget(this);

        _scroll_area = new QScrollArea(this);
        _scroll_area->setWidget(_side_widget);
        _scroll_area->setSizePolicy(_side_widget->sizePolicy());
        _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        _gl_widget = new GLWidget(this);
        _gl_widget->_sideWidget = _side_widget;

        centralWidget()->setLayout(new QHBoxLayout());
        centralWidget()->layout()->addWidget(_gl_widget);
        centralWidget()->layout()->addWidget(_scroll_area);

        // creating a signal slot mechanism between the rendering context and the side widget
        connect(_side_widget->rotate_x_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_x(int)));
        connect(_side_widget->rotate_y_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_y(int)));
        connect(_side_widget->rotate_z_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_z(int)));

        connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_zoom_factor(double)));

        connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_x(double)));
        connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_y(double)));
        connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_z(double)));
        connect(_side_widget->comboBox,SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(change_curve(int)));
        connect(_side_widget->scaleSpinBox,SIGNAL(valueChanged(int)),_gl_widget,SLOT(change_scale(int)));        
        connect(_side_widget->surfaceCombo,SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(change_surface(int)));
        connect(_side_widget->homeworkChooser,SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(change_homework(int)));
        connect(_side_widget->ArcAlphaSpinBox,SIGNAL(valueChanged(double)),_gl_widget,SLOT(change_ArcAlpha(double)));

        connect(_side_widget->ArcInsertButton, SIGNAL(clicked()),_gl_widget,SLOT(insertArc()));
        connect(_side_widget->ArcContinueButton, SIGNAL(clicked()),_gl_widget,SLOT(continueArc()));
        connect(_side_widget->ArcJoinButton, SIGNAL(clicked()),_gl_widget,SLOT(joinArcs()));

        connect(_side_widget->ArcTransformPointIndex, SIGNAL(valueChanged(int)),_gl_widget,SLOT(changeTransformPointIndex(int)));
        connect(_side_widget->ArcTransformX,SIGNAL(valueChanged(double)),_gl_widget,SLOT(changeTransformX(double)));
        connect(_side_widget->ArcTransformY,SIGNAL(valueChanged(double)),_gl_widget,SLOT(changeTransformY(double)));
        connect(_side_widget->ArcTransformZ,SIGNAL(valueChanged(double)),_gl_widget,SLOT(changeTransformZ(double)));

        connect(_side_widget->ArcMergeButton, SIGNAL(clicked()),_gl_widget,SLOT(mergeArcs()));
        //update sphere stuff
        connect(_side_widget->ArcContinueSpinBox,SIGNAL(valueChanged(int)),_gl_widget,SLOT(updateSpheresOnArcSelected(int)));
        connect(_side_widget->ArcJoinFirstIndex,SIGNAL(valueChanged(int)),_gl_widget,SLOT(updateSpheresOnArcSelected(int)));
        connect(_side_widget->ArcJoinSecondIndex,SIGNAL(valueChanged(int)),_gl_widget,SLOT(updateSpheresOnArcSelected(int)));
        connect(_side_widget->ArcTransformArcIndex,SIGNAL(valueChanged(int)),_gl_widget,SLOT(updateSpheresOnArcSelected(int)));
        connect(_side_widget->ArcMergeFirstIndex,SIGNAL(valueChanged(int)),_gl_widget,SLOT(updateSpheresOnArcSelected(int)));
        connect(_side_widget->ArcMergeSecondIndex,SIGNAL(valueChanged(int)),_gl_widget,SLOT(updateSpheresOnArcSelected(int)));
        //Patch
        connect(_side_widget->PatchInsertButton, SIGNAL(clicked()),_gl_widget,SLOT(insertPatch()));
        connect(_side_widget->PatchInsertButtonX, SIGNAL(clicked()),_gl_widget,SLOT(insertPatchX()));
        connect(_side_widget->PatchInsertButtonY, SIGNAL(clicked()),_gl_widget,SLOT(insertPatchY()));
        connect(_side_widget->PatchClearButton, SIGNAL(clicked()),_gl_widget,SLOT(clearPatch()));
        connect(_side_widget->PatchContinueButton, SIGNAL(clicked()),_gl_widget,SLOT(continuePatch()));
        connect(_side_widget->PatchContinueSpinBox, SIGNAL(valueChanged(int)),_gl_widget,SLOT(updateSelectionCurveOnContinue()));
        connect(_side_widget->PatchContinueDirection, SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(updateSelectionCurveOnContinue()));
        connect(_side_widget->PatchJoinButton, SIGNAL(clicked()),_gl_widget,SLOT(joinPatch()));        
        connect(_side_widget->PatchJoinFirstIndex, SIGNAL(valueChanged(int)),_gl_widget,SLOT(updateSelectionCurveOnJoinFirst()));
        connect(_side_widget->PatchJoinSecondIndex, SIGNAL(valueChanged(int)),_gl_widget,SLOT(updateSelectionCurveOnJoinSecond()));
        connect(_side_widget->PatchJoinFirstDirection, SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(updateSelectionCurveOnJoinFirst()));
        connect(_side_widget->PatchJoinSecondDirection, SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(updateSelectionCurveOnJoinSecond()));

        connect(_side_widget->PatchMergeFirstIndex, SIGNAL(valueChanged(int)),_gl_widget,SLOT(updateSelectionCurveOnMergeFirst()));
        connect(_side_widget->PatchMergeSecondIndex, SIGNAL(valueChanged(int)),_gl_widget,SLOT(updateSelectionCurveOnMergeSecond()));
        connect(_side_widget->PatchMergeFirstDirection, SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(updateSelectionCurveOnMergeFirst()));
        connect(_side_widget->PatchMergeSecondDirection, SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(updateSelectionCurveOnMergeSecond()));

        //Transform
        connect(_side_widget->PatchTransformPatchIndex, SIGNAL(valueChanged(int)),_gl_widget,SLOT(changeTransformPointsIndex()));
        connect(_side_widget->PatchTransformPointJ, SIGNAL(valueChanged(int)),_gl_widget,SLOT(changeTransformPointsIndex()));
        connect(_side_widget->PatchTransformPointI, SIGNAL(valueChanged(int)),_gl_widget,SLOT(changeTransformPointsIndex()));
        connect(_side_widget->PatchTransformX,SIGNAL(valueChanged(double)),_gl_widget,SLOT(transformPatchX()));
        connect(_side_widget->PatchTransformY,SIGNAL(valueChanged(double)),_gl_widget,SLOT(transformPatchY()));
        connect(_side_widget->PatchTransformZ,SIGNAL(valueChanged(double)),_gl_widget,SLOT(transformPatchZ()));
        connect(_side_widget->PatchMergeButton, SIGNAL(clicked()),_gl_widget,SLOT(mergePatches()));
        //Isoparametric stuff
        connect(_side_widget->PatchIsoUCheckBox, SIGNAL(clicked(bool)),_gl_widget,SLOT(togglePatchUIso(bool)));
        connect(_side_widget->PatchIsoVCheckBox, SIGNAL(clicked(bool)),_gl_widget,SLOT(togglePatchVIso(bool)));
        // Shader stuff
        connect(_side_widget->ShaderCheckbox, SIGNAL(clicked(bool)),_gl_widget,SLOT(setShaderOnOrOff(bool)));
        connect(_side_widget->ShaderComboBox, SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(changeSelectedShader(int)));
        connect(_side_widget->ShaderComboBox, SIGNAL(currentIndexChanged(int)),_gl_widget,SLOT(changeSelectedShader(int)));

        // Reflection stuff
        connect(_side_widget->ShaderReflectionScale, SIGNAL(valueChanged(double)),_gl_widget,SLOT(shaderChangeReflectionScale(double)));
        connect(_side_widget->ShaderReflectionSmoothing, SIGNAL(valueChanged(double)),_gl_widget,SLOT(shaderChangeReflectionSmoothing(double)));
        connect(_side_widget->ShaderReflectionShading, SIGNAL(valueChanged(double)),_gl_widget,SLOT(shaderChangeReflectionShading(double)));

        // Toon stuff
        connect(_side_widget->ShaderToonButtonOk, SIGNAL(clicked()),_gl_widget,SLOT( shaderChangeToonOutline()));

        //Persistence
        //Save arcs
        connect(_side_widget->ArcSaveButton, SIGNAL(clicked()),_gl_widget,SLOT( saveArcs()));
        //Read arcs
        connect(_side_widget->ArcOpenButton, SIGNAL(clicked()),_gl_widget,SLOT( readArcs()));
        connect(_side_widget->PatchSaveButton, SIGNAL(clicked()),_gl_widget,SLOT( savePatches()));
        //Read Patchs
        connect(_side_widget->PatchOpenButton, SIGNAL(clicked()),_gl_widget,SLOT( readPatches()));
        //Texture application,disabling
        connect(_side_widget->PatchApplyButton, SIGNAL(clicked()),_gl_widget,SLOT( applyTexture()));
        connect(_side_widget->PatchDisableButton, SIGNAL(clicked()),_gl_widget,SLOT( disableTexture()));
    }

    //--------------------------------
    // implementation of private slots
    //--------------------------------
    void MainWindow::on_action_Quit_triggered()
    {
        qApp->exit(0);
    }
}
