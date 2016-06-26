/*
 * Author: Alexander Rajula
 * E-mail: superrajula@gmail.com
 * Description:
 *  This class enables an application to log data.
 *  The data may be output to a terminal, to a file, to a network or all of these combined.
 */

#ifndef _logger_hpp_
#define _logger_hpp_

namespace logging_services{

#define MAX_PREFIX_STRING_LENGTH  256

typedef enum{
  Terminal  = 0,
  File      = 1,
  Network   = 2
}Data_Destination_Type;

class logger{
  private:
    char  prefix_string[MAX_PREFIX_STRING_LENGTH];

    bool  terminal_output_enabled;
    bool  file_output_enabled;
    bool  network_output_enabled;

    bool  insert_timestamp;
  public:
    logger();
    ~logger();

    /*
     * This function enables setting of a prefix string which will be
     * inserted at the start of recorded strings.
     *
     * The maximum size of the prefix_string has been capped to MAX_PREFIX_STRING_LENGTH bytes.
     *
     * Returns 0 on failure.
     */
    int set_prefix(const char* string, unsigned int string_length);

    /*
     * This function enables insertion of a timestamp in all recorded data.
     */
    void enable_timestamping(void);

    /*
     * This function disables insertion of a timestamp in all recorded data.
     */
    void disable_timestamping(void);

    /*
     * This function turns on distribution of data to a specific type of destination.
     */
    void enable_data_destination(Data_Destination_Type  destination);

    /*
     * This function turns off distribution of data to a specific type of destination.
     */
    void disable_data_destination(Data_Destination_Type destination);

};

}

#endif
