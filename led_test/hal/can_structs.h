#ifndef CAN_STRUCTS_H
#define CAN_STRUCTS_H

#include <stdint.h>

/**< Baudrates */
enum {
  CAN_BITRATE_125K,
  CAN_BITRATE_250K,
  CAN_BITRATE_500K,
  CAN_BITRATE_1M,
  CAN_BITRATE_2M,
  CAN_BITRATE_4M,
  CAN_BITRATE_LAST
};

/**
 * \brief CAN Message Format
 */
enum can_format {
	CAN_FMT_STDID, /**< Standard Format, 11 bits identifier */
	CAN_FMT_EXTID  /**< Extended Format, 29 bits identifier */
};

/**
 * \brief CAN Message Type
 */
enum can_type {
  CAN_TYPE_DATA,   /*!< A DATA FRAME carries data from a transmitter to the
	                    receivers.*/
  CAN_TYPE_REMOTE, /*!< A REMOTE FRAME is transmitted by a bus unit to request
	                     the transmission of the DATA FRAME with the same
	                     IDENTIFIER */
  CAN_TYPE_FD,
  CAN_TYPE_FD_BRS
};

/**
 * \brief CAN Filter
 */
struct can_filter {
	uint32_t id;   /**< Message identifier */
	uint32_t mask; /**< Mask applied to id */
};

/**
 * \brief CAN Message
 */
struct can_message {
	uint32_t        id;   /**< Message identifier */
	enum can_type   type; /**< Message Type */
	uint8_t *       data; /**< Pointer to Message Data */
	uint8_t         len;  /**< Message Length */
	enum can_format fmt;  /**< Identifier format, CAN_STD, CAN_EXT */
};


/**
 * \brief CAN Errors
 */
struct can_errors {
  bool    rx_err_passive; /**< Receive error passive */
  uint8_t rx_err_counter; /**< Receive error counter */
  uint8_t tx_err_counter; /**< Transmit error counter */
};

#endif
