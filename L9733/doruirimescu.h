/**
 *  @file doruirimescu.h
 *  @author Doru Irimescu
 *  @brief Driver interface for programming the L9733 integrated circuit for flight purposes.
 *  I chose not to make unions with bitfields, because writing each bit individually makes it more clear in code.
 *  However, two macros is provided for clearing and setting the bitfields for convenience.
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
 * @brief  Bitfield representing driver diagnostic mode configuration
 * Writing a 0 sets the corresponding output in no Latch Mode.
 * Writing a 1 sets the corresponding output in Latch Mode.
 */
typedef struct
{
    uint8_t diag_1 : 1;
    uint8_t diag_2 : 1;
    uint8_t diag_3 : 1;
    uint8_t diag_4 : 1;
    uint8_t diag_5 : 1;
    uint8_t diag_6 : 1;
    uint8_t diag_7 : 1;
    uint8_t diag_8 : 1;

} diag_mode_t;

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
 * @brief  Structure representing a fault report.
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
 * @brief  Programs the chip with an output status configuration. Returns status.
 *
 * @param  in_config : output status configuration
 * @param  out_status : fault status report
 */
void writeOutputStatusConfiguration(const output_status_t const* in_config, fault_report_t const* out_status);

/**
 * @brief  Programs the chip with a diagnostic mode configuration. Returns status.
 *
 * @param  in_config : diagnostic mode configuration
 * @param  out_status : fault status report
 */
void writeDianosticModeConfiguration(const diag_mode_t const* in_config, fault_report_t const* out_status);

/**
 * @brief  Programs the chip with an overcurrent protection configuration. Returns status.
 *
 * @param  in_config : overcurrent protection configuration
 * @param  out_status : fault status report
 */
void writeOvercurrentProtectionConfiguration(const overcurrent_protection_t const* in_config, fault_report_t const* out_status);

#endif
