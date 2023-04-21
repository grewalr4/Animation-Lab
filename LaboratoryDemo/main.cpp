/**
 * @file main.cpp
 * @author Charles B. Owen
 *
 * Main entry point for laboratory demonstrator program
 *
 * Do not modify this file!
 */
#include "pch.h"
#include "LaboratoryDemoBaseApp.h"
#include "LaboratoryIsolator.h"

//<editor-fold desc="LaboratoryDemoApp">
/**
 * LaboratoryDemo main application class.
 * Most of the work is actually done in the base class.
 */
class LaboratoryDemoApp : public LaboratoryDemoBaseApp {
public:
    /**
     * Create the laboratory isolator, which contains the laboratory we are displaying.
     * @param resourcesDir Directory containing the resources for the program
     * @return LaboratoryIsolator object
     */
    std::shared_ptr<ILaboratoryIsolator> CreateIsolator(std::wstring resourcesDir) override
    {
        return std::make_shared<LaboratoryIsolator>(resourcesDir);
    }

};
//</editor-fold>

wxIMPLEMENT_APP(LaboratoryDemoApp);

