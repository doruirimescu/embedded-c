/**
 *  @file doruirimescu.h
 *  @author Doru Irimescu
 *  @brief Driver interface for programming the L9733 integrated circuit for flight purposes
 *  I chose not to make unions with bitfields, because writing each bit individually makes it more clear in code.
 *  However, two macros are provided for clearing and setting the bitfields for convenience.
 *  It is best to include the spi.h header in the source file, since it is only used there.
 *
 *  The naming convention which I have used: preffix _t for structure, suffix _e for enum. camelCase naming for functions.
 *  For function parameters, suffix in_ if the parameter is an input, out_ if the parameter is an output and inout_ if
 *  the parameter is both used as an input and output (not the case in here). In addition, the type of the parameter is
 *  specified followed by the parameter name. Eg. in_ptParam denotes an input parameter which
 *  is a pointer to structure.
 */

#ifndef _DORUIRIMESCU_H_
#define _DORUIRIMESCU_H_

/**
 * @brief  Clears the bits of a one-byte bitfield.
 *
 */
#define CLEAR_BITFIELD_BYTE(s) *((uint8_t*)&s) = 0

/**
 * @brief  Sets the bits of a one-byte bitfield.
 *
 */
#define SET_BITFIELD_BYTE(s) *((uint8_t*)&s) = 0xFF

/**
 * @brief  Bitfield representing an output status configuration
 * Writing a 0 turns an output off. Writing a 1 turns the output on.
 */
typedef struct
{
    uint8_t out_1 : 1;
    uint8_t out_2 : 1;
    uint8_t out_3 : 1;
    uint8_t out_4 : 1;
    uint8_t out_5 : 1;
    uint8_t out_6 : 1;
    uint8_t out_7 : 1;
    uint8_t out_8 : 1;

} output_status_t;

/**
 * @brief  Bitfield representing driver diagnosis mode configuration
 * Writing a 0 sets the corresponding output in no Latch Mode.
 * Writing a 1 sets the corresponding output in Latch Mode.
 */
typedef struct
{
    uint8_t diagnosis_1 : 1;
    uint8_t diagnosis_2 : 1;
    uint8_t diagnosis_3 : 1;
    uint8_t diagnosis_4 : 1;
    uint8_t diagnosis_5 : 1;
    uint8_t diagnosis_6 : 1;
    uint8_t diagnosis_7 : 1;
    uint8_t diagnosis_8 : 1;

} diagnosis_mode_t;

/**
 * @brief  Bitfield representing driver overcurrent protection configuration
 * Writing a 0 turns off the overcurrent protection on the corresponding output.
 * Writing a 1 turns on the overcurrent protection on the corresponding output.
 */
typedef struct
{
    uint8_t ilim_1 : 1;
    uint8_t ilim_2 : 1;
    uint8_t ilim_3 : 1;
    uint8_t ilim_4 : 1;
    uint8_t ilim_5 : 1;
    uint8_t ilim_6 : 1;
    uint8_t ilim_7 : 1;
    uint8_t ilim_8 : 1;
} overcurrent_protection_t;

/**
 * @brief  Enumeration representing a fault status for one output.
 *
 */
typedef enum
{
    NO_FAULT_PRESENT,
    OPEN_LOAD,
    SHORT_CIRCUIT_OVERCURRENT
} fault_status_e;

/**
 * @brief  Structure representing a fault report for each output channel.
 *
 */
typedef struct
{
    fault_status_e out_1;
    fault_status_e out_2;
    fault_status_e out_3;
    fault_status_e out_4;
    fault_status_e out_5;
    fault_status_e out_6;
    fault_status_e out_7;
    fault_status_e out_8;
} fault_report_t;

/**
 * @brief  Programs the chip with an output status configuration. Returns fault report.
 *
 * @param  in_ptConfig : output status configuration
 * @param  out_ptStatus : fault status report
 */
void writeOutputStatusConfiguration(const output_status_t const* in_ptConfig, fault_report_t const* out_ptStatus);

/**
 * @brief  Programs the chip with a diagnosis mode configuration. Returns fault report.
 *
 * @param  in_ptConfig : diagnosis mode configuration
 * @param  out_ptStatus : fault status report
 */
void writeDianosticModeConfiguration(const diagnosis_mode_t const* in_ptConfig, fault_report_t const* out_ptStatus);

/**
 * @brief  Programs the chip with an overcurrent protection configuration. Returns fault report.
 *
 * @param  in_ptConfig : overcurrent protection configuration
 * @param  out_ptStatus : fault status report
 */
void writeOvercurrentProtectionConfiguration(const overcurrent_protection_t const* in_ptConfig, fault_report_t const* out_ptStatus);

#endif
