#ifndef OBD2_PIDS_H
#define OBD2_PIDS_H

/* List of On-board diagnostics (OBD) Parameter IDs (PID) */

/* PIDs for OBD-II Mode 0x01 */
enum{
	SUPPORTED_PIDS 										= 0x00, /* Bit encoded [A7..D0] == [PID $01.. PID $20] */
	MONITOR_STATUS										= 0x01,	/* Bit encoded */
	FREEZE_DTC												= 0x02,
	FUEL_SYSTEM_STATUS								= 0x03,	/* Bit encoded */
	ENGINE_LOAD												= 0x04,	/* Min: 0, 		Max: 100 		Unit: % 					Formula: A*100/255 */
	ENGINE_COOLANT_TEMP								= 0x05, /* Min: -40 	Max: 215 		Unit: Centigrade	Formula: A-40 */
	SHORT_TERM_FUEL_PERC_TRIM_BANK_1	= 0x06, /* Min: -100 	Max: 99.22 	Unit: % 					Formula: (A-128)*100/128 Note: -100 means subtracting fuel (rich condition) 99.22 means adding fuel (lean condition) */
	SHORT_TERM_FUEL_PERC_TRIM_BANK_11	= 0x07, /* Min: -100 	Max: 99.22 	Unit: % 					Formula: (A-128)*100/128 Note: -100 means subtracting fuel (rich condition) 99.22 means adding fuel (lean condition) */
	SHORT_TERM_FUEL_PERC_TRIM_BANK_2	= 0x08, /* Min: -100 	Max: 99.22 	Unit: % 					Formula: (A-128)*100/128 Note: -100 means subtracting fuel (rich condition) 99.22 means adding fuel (lean condition) */
	SHORT_TERM_FUEL_PERC_TRIM_BANK_22	= 0x09, /* Min: -100 	Max: 99.22	Unit: % 					Formula: (A-128)*100/128 Note: -100 means subtracting fuel (rich condition) 99.22 means adding fuel (lean condition) */
	FUEL_PRESSURE											= 0x0A, /* Min: 0			Max: 765		Unit: kPa					Formula:	A*3 					*/
	INTAKE_MANIFOLD_PRESSURE					= 0x0B, /* Min: 0			Max: 255		Unit: kPa					Formula:	A 						*/
	ENGINE_RPM												= 0x0C, /* Min: 0			Max: 16383.75	Unit: rpm				Formula: ((A*256)+B)/4	*/
	VEHICLE_SPEED											= 0x0D,	/* Min: 0			Max: 255		Unit: km/h				Formula: A 							*/
	TIMING_ADVANCE										= 0x0E, /* Min: -64		Max: 63.5		Unit: degrees			Formula:	(A-128)/2			Note: Relative to #1 cylinder. */
	INTAKE_AIR_TEMPERATURE						= 0x0F, /* Min: -40		Max: 215		Unit: Centigrade	Formula:	A-40						*/
	MAF_AIR_FLOW_RATE									= 0x10, /* Min: 0			Max: 655.35	Unit:	grams/s			Formula:	((A*256)+B/100	*/
	THROTTLE_POSITION									= 0x11,	/* Min: 0			Max: 100		Unit: %						Formula:	A*100/255				*/
	COMMANDED_SECONDARY_AIR_STATUS		= 0x12, /* Bit encoded */
	OXYGEN_SENSORS_PRESENT						= 0x13, /* [A0..A3] == Bank 1, Sensors1-4. [A4..A7] == Bank2 .. */

	CONFORMED_OBD_STANDARDS						= 0x1C, /* Bit encoded */

	AUXILIARY_INPUT_STATUS						= 0x1E, /* A0 == Power Take Off status - 1 -> Active */
	RUNTIME_SINCE_ENGINE_START				= 0x1F, /* Min: 0			Max: 65535	Unit: seconds			Formula: (A*256)+B 					*/

	DISTANCE_TRAVELED_WITH_CEL				= 0x21,	/* Min: 0			Max: 65536	Unit: kilometers	Formula: (A*256)+B					*/
	FUEL_RAIL_PRESSURE								= 0x22, /* Min: 0			Max: 5177.265	Unit: kPa				Formula: ((A*256)+B)*0.079	*/
	FUEL_RAIL_PRESSURE_DIRECT_INJECT	= 0x23,	/* Min: 0			Max: 655350		Unit: kPa				Formula: ((A*256)+B)*10			*/

	COMMANDED_EXHAUST_GAS_RECIRCULATION	= 0x2C,	/* Min: 0		Max: 100			Unit: %					Formula: A*100/255					*/
	EXHAUST_GAS_RECIRCULATION_ERROR		= 0x2D,	/* Min: -100	Max: 99.22		Unit: %					Formula: (A-128)*100/128		*/
	COMMANDED_EVAPORATIVE_PURGE				= 0x2E,	/* Min: 0			Max: 100			Unit: %					Formula: A*100/255					*/
	FUEL_LEVEL_INPUT									= 0x2F,	/* Min: 0			Max: 100			Unit: %					Formula: A*100/255					*/
	NUMBER_OF_WARMUPS_SINCE_CODES_CLEARED	=	0x30,	/* Min: 0	Max: 255			Unit: N/A				Formula: A									*/
	DISTANCE_TRAVELED_SINCE_CODES_CLEARED = 0x31,	/* Min: 0 Max: 65535		Unit: kilometers	Formula:	(A*256)+B				*/
	EVAPORATIVE_SYSTEM_VAPOR_PRESSURE	= 0x32,	/* Min: -8192	Max: 8192			Unit:	Pa				Formula: ((A*256)+B/4		Note: A and B are 2's complement signed		*/
	BAROMETRIC_PRESSURE								= 0x33, /* Min: 0			Max: 255			Unit: kPa				Formula: A									*/

	CONTROL_MODULE_VOLTAGE						= 0x42, /* Min: 0			Max: 65.535		Unit: Volts			Formula: ((A*256)+B)/1000		*/

	RELATIVE_THROTTLE_POSITION				= 0x45, /* Min: 0			Max: 100			Unit: %					Formula: A*100/255					*/
	AMBIENT_AIR_TEMPERATURE						= 0x46, /* Min: -40		Max: 215			Unit: Centigrade	Formula:	A-40						*/

	COMMANDED_THROTTLE_ACTUATOR				= 0x4C, /* Min: 0			Max: 100			Unit: %					Formula: A*100/255					*/

	FUEL_TYPE													= 0x51, /* Enum */
	ETHANOL_FUEL_PERCENTAGE						= 0x52, /* Min: 0			Max: 100			Unit: %					Formula: A*100/255					*/
	ENGINE_OIL_TEMPERATURE						= 0x5C,	/* Min: -40		Max: 210			Unit: Centigrade	Formula: A-40							*/
	FUEL_INJECTION_TIMING							= 0x5D, /* Min: -210	Max: 301.992	Unit: Degrees		Formula: (((A*256)+B)-26880)/128	*/
	ENGINE_FUEL_RATE									= 0x5E,	/* Min: 0			Max: 3212.75	Unit: Litres/hour	Formula:	((A*256)+B)*0.05	*/

	DRIVER_DEMAND_ENGINE_TORQUE				= 0x61,	/* Min: -125	Max: 125				Unit: %					Formula: A-125							*/
	ACTUAL_ENGINE_TORQUE							= 0x62,	/* Min: -125	Max: 125				Unit: %					Formula: A-125							*/
	ENGINE_REFERENCE_TORQUE						= 0x63, /* Min: 0			Max: 65535			Unit:	Nm				Formula: A*256+B						*/

	MASS_AIR_FLOW_SENSOR							= 0x66,
	ENGINE_COOLANT_TEMPERATURE				= 0x67,
	INTAKE_AIR_TEMPERATURE_SENSOR			= 0x68,

	TURBOCHARGER_COMPRESSOR_INLET_PRESSURE	= 0x6F,
	BOOST_PRESSURE_CONTROL									= 0x70,
	WASTEGATE_CONTROL												= 0x72,
	EXHAUST_PRESSURE												= 0x73,
	TURBOCHARGER_RPM												= 0x74,
	TURBOCHARGER_TEMPERATURE_1							= 0x75,
	TURBOCHARGER_TEMPERATURE_2							= 0x76,
	CHARGE_AIR_COOLER_TEMPERATURE						= 0x77
}

/* PIDs for OBD-II Mode 0x02 */
enum{
	DTC_ORIGIN_FOR_FREEZE_FRAME = 0x02
}

/* PIDs for OBD-II Mode 0x03 */
enum{
	REQUEST_TROUBLE_CODES = 0x00
}

/* PIDs for OBD-II Mode 0x04 */
enum{
	CLEAR_TROUBLE_CODES	= 0x00
}

/* PIDs for OBD-II Mode 0x09 */
enum{
	SUPPORTED_PIDS 																= 0x00, /* Bit encoded [A7..D0] == [PID $01.. PID $20] */
	VEHICLE_IDENTIFICATION_MESSAGE_COUNT					= 0x01,
	VEHICLE_IDENTIFICATION_NUMBER									= 0x02, /* Note: Returns 17-20 bytes Formula: ASCII-encoded and left-padded with 0x00 if needed. */
	CALIBRATION_ID_MESSAGE_COUNT									= 0x03,
	CALIBRATION_ID																= 0x04, /* Note: Up to 16 ASCII characters. Data bytes not used will be reported as 0x00 */
	CALIBRATION_VERIFICATION_NUMBER_MESSAGE_COUNT	= 0x05,
	CALIBRATION_VERIFICATION_NUMBERS							= 0x06,	/* Note: Raw data left-padded with 0x00. Usually displayed as hex string. */
	INHOUSE_PERFORMANCE_TRACKING_MESSAGE_COUNT		= 0x07,	
	INHOUSE_PERFORMANCE_TRACKING_OTTO							= 0x08, /* Note: 4 or 5 messages, eachone containing 4 bytes. */
	ECU_NAME_MESSAGE_COUNT												= 0x09,
	ECU_NAME																			= 0x0A, /* Note: ASCII-encoded. Right-padded with 0x00 */
	INHOUSE_PERFORMANCE_TRACKING_DIESEL						= 0x0B
}

typedef enum{
	OBD_II_CARB 							= 1,
	OBD_EPA										= 2,
	OBD_AND_OBD-II						= 3,
	OBD_I											= 4,
	NOT_OBD										= 5,
	EOBD_EUROPE								= 6,
	EOBD_AND_OBD_II						= 7,
	EOBD_AND_OBD							= 8,
	EOBD_AND_OBD_AND_OBD_II		= 9,
	JOBD_JAPAN								= 10,
	JOBD_AND_OBD_II						= 11,
	JOBD_AND_EOBD							= 12,
	JOBD_AND_EOBD_AND_OBD_II	= 13,
	EMD 											= 17,
	EMD_PLUS									= 18,
	HD_OBD_C									= 19,
	HD_OBD										= 20,
	WWH_OBD 									= 21,
	HD_EOBD_I 								= 23,
	HD_EOBD_I_N								= 24,
	HD_EOBD_II								= 25,
	HD_EOBD-II_N							= 26,
	OBDBr_1										= 28,
	OBDBr_2										= 29,
	KOBD											= 30,
	IOBD_I										= 31,
	IOBD_II										= 32,
	HD_EOBD_IV								= 33
}CONFORMED_OBD_STANDARD;

typedef enum{
	NOT_AVAILABLE											= 0,
	GASOLINE													= 1,
	METHANOL													= 2,
	ETHANOL														= 3,
	DIESEL														= 4,
	LPG																= 5,
	CNG																= 6,
	PROPANE														= 7,
	ELECTRIC													= 8,
	BIFUEL_ON_GASOLINE								= 9,
	BIFUEL_ON_METHANOL								= 10,
	BIFUEL_ON_ETHANOL									= 11,
	BIFUEL_ON_LPG											= 12,
	BIFUEL_ON_CNG											= 13,
	BIFUEL_ON_PROPANE									= 14,
	BIFUEL_ON_ELECTRIC								= 15,
	BIFUEL_ON_ELECTRIC_AND_COMBUSTION	= 16,
	HYBRID_GASOLINE										= 17,
	HYBRID_ETHANOL										= 18,
	HYBRID_DIESEL											= 19,
	HYBRID_ELECTRIC										= 20,
	HYBRID_ON_ELECTRIC_AND_COMBUSTION	= 21,
	HYBRID_REGENERATIVE								= 22,
	BIFUEL_ON_DIESEL									= 23
}FUEL_TYPE;

#endif
