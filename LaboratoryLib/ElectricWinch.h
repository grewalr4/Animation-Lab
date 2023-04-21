/**
 * @file ElectricWinch.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ELECTRICElectricWinch_H
#define CANADIANEXPERIENCE_ELECTRICElectricWinch_H

#include "Winch.h"
#include "PowerSink.h"

/**
 * ElectricWinch in the laboratory which shares
 * functionality with the Winch
 */
class ElectricWinch : public Winch {
private:

    /// Power sink for this electric ElectricWinch
    PowerSink mPowerSink;

    /// Power on?
    bool mOn = false;

public:

    ElectricWinch(std::wstring imagesDir);

    /// Destructor
    virtual ~ElectricWinch() = default;

    /// Copy constructor/disabled
    ElectricWinch(const ElectricWinch&) = delete;

    /// Assignment operator/disabled
    void operator=(const ElectricWinch&) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    /**
     * Get the power sink for this electric winch
     * @return power sink as a pointer
     */
    PowerSink* GetPowerSink() { return &mPowerSink; }

    double Power(double voltage);

    void Update(double time);
};

#endif //CANADIANEXPERIENCE_ELECTRICElectricWinch_H
