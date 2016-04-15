//----------------------------------------------------------------------------
// user_logic.v - module
//----------------------------------------------------------------------------
//
// ***************************************************************************
// ** Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.            **
// **                                                                       **
// ** Xilinx, Inc.                                                          **
// ** XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"         **
// ** AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND       **
// ** SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,        **
// ** OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,        **
// ** APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION           **
// ** THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,     **
// ** AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE      **
// ** FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY              **
// ** WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE               **
// ** IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR        **
// ** REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF       **
// ** INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS       **
// ** FOR A PARTICULAR PURPOSE.                                             **
// **                                                                       **
// ***************************************************************************
//
//----------------------------------------------------------------------------
// Filename:          user_logic.v
// Version:           1.00.a
// Description:       User logic module.
// Date:              Wed Apr 13 17:31:01 2016 (by Create and Import Peripheral Wizard)
// Verilog Standard:  Verilog-2001
//----------------------------------------------------------------------------
// Naming Conventions:
//   active low signals:                    "*_n"
//   clock signals:                         "clk", "clk_div#", "clk_#x"
//   reset signals:                         "rst", "rst_n"
//   generics:                              "C_*"
//   user defined types:                    "*_TYPE"
//   state machine next state:              "*_ns"
//   state machine current state:           "*_cs"
//   combinatorial signals:                 "*_com"
//   pipelined or register delay signals:   "*_d#"
//   counter signals:                       "*cnt*"
//   clock enable signals:                  "*_ce"
//   internal version of output port:       "*_i"
//   device pins:                           "*_pin"
//   ports:                                 "- Names begin with Uppercase"
//   processes:                             "*_PROCESS"
//   component instantiations:              "<ENTITY_>I_<#|FUNC>"
//----------------------------------------------------------------------------

`uselib lib=unisims_ver
`uselib lib=proc_common_v3_00_a

module user_logic
(
  // -- ADD USER PORTS BELOW THIS LINE ---------------
  // --USER ports added here 
  // -- ADD USER PORTS ABOVE THIS LINE ---------------

  // -- DO NOT EDIT BELOW THIS LINE ------------------
  // -- Bus protocol ports, do not add to or delete 
  Bus2IP_Clk,                     // Bus to IP clock
  Bus2IP_Resetn,                  // Bus to IP reset
  Bus2IP_Data,                    // Bus to IP data bus
  Bus2IP_BE,                      // Bus to IP byte enables
  Bus2IP_RdCE,                    // Bus to IP read chip enable
  Bus2IP_WrCE,                    // Bus to IP write chip enable
  IP2Bus_Data,                    // IP to Bus data bus
  IP2Bus_RdAck,                   // IP to Bus read transfer acknowledgement
  IP2Bus_WrAck,                   // IP to Bus write transfer acknowledgement
  IP2Bus_Error                    // IP to Bus error response
  // -- DO NOT EDIT ABOVE THIS LINE ------------------
); // user_logic

// -- ADD USER PARAMETERS BELOW THIS LINE ------------
// --USER parameters added here 
// -- ADD USER PARAMETERS ABOVE THIS LINE ------------

// -- DO NOT EDIT BELOW THIS LINE --------------------
// -- Bus protocol parameters, do not add to or delete
parameter C_NUM_REG                      = 11;
parameter C_SLV_DWIDTH                   = 32;
// -- DO NOT EDIT ABOVE THIS LINE --------------------

// -- ADD USER PORTS BELOW THIS LINE -----------------
// --USER ports added here 
// -- ADD USER PORTS ABOVE THIS LINE -----------------

// -- DO NOT EDIT BELOW THIS LINE --------------------
// -- Bus protocol ports, do not add to or delete
input                                     Bus2IP_Clk;
input                                     Bus2IP_Resetn;
input      [C_SLV_DWIDTH-1 : 0]           Bus2IP_Data;
input      [C_SLV_DWIDTH/8-1 : 0]         Bus2IP_BE;
input      [C_NUM_REG-1 : 0]              Bus2IP_RdCE;
input      [C_NUM_REG-1 : 0]              Bus2IP_WrCE;
output     [C_SLV_DWIDTH-1 : 0]           IP2Bus_Data;
output                                    IP2Bus_RdAck;
output                                    IP2Bus_WrAck;
output                                    IP2Bus_Error;
// -- DO NOT EDIT ABOVE THIS LINE --------------------

//----------------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------------

  // --USER nets declarations added here, as needed for user logic
  wire [31:0] lowbeta, oldlowbeta, lowbeta1;
  wire [31:0] highbeta, oldhighbeta, highbeta1;
  wire [31:0] lowgamma, oldlowgamma, lowgamma1;
  wire [31:0] lowbeta_result;
  wire [31:0] highbeta_result;
  wire [31:0] lowgamma_result;
  wire [31:0] attention;
  wire [31:0] knn_value;
  // Nets for user logic slave model s/w accessible register example
  reg        [C_SLV_DWIDTH-1 : 0]           slv_reg0;
  reg        [C_SLV_DWIDTH-1 : 0]           slv_reg1;
  reg        [C_SLV_DWIDTH-1 : 0]           slv_reg2;
  reg        [C_SLV_DWIDTH-1 : 0]           slv_reg3;
  reg        [C_SLV_DWIDTH-1 : 0]           slv_reg4;
  reg        [C_SLV_DWIDTH-1 : 0]           slv_reg5;
  reg        [C_SLV_DWIDTH-1 : 0]           slv_reg6;
  reg        [C_SLV_DWIDTH-1 : 0]           slv_reg7;
  reg        [C_SLV_DWIDTH-1 : 0]           slv_reg8;
  reg        [C_SLV_DWIDTH-1 : 0]           slv_reg9;
  reg        [C_SLV_DWIDTH-1 : 0]           slv_reg10;
  wire       [10 : 0]                       slv_reg_write_sel;
  wire       [10 : 0]                       slv_reg_read_sel;
  reg        [C_SLV_DWIDTH-1 : 0]           slv_ip2bus_data;
  wire                                      slv_read_ack;
  wire                                      slv_write_ack;
  integer                                   byte_index, bit_index;

  // USER logic implementation added here
  assign lowbeta = slv_reg0;
  assign highbeta = slv_reg1;
  assign lowgamma = slv_reg3;
  assign oldlowbeta = slv_reg6;
  assign oldhighbeta = slv_reg7;
  assign oldlowgamma = slv_reg8;
  assign lowbeta_result = (lowbeta1+oldlowbeta) >> 1;
  assign highbeta_result = (highbeta1+oldhighbeta) >> 1;
  assign lowgamma_result = (lowgamma1+oldlowgamma) >> 1;
  assign attention = slv_reg4;
  assign knn_value = slv_reg9;
  
  Filter filter_lowbeta(lowbeta, oldlowbeta, 2'b00, lowbeta1);
  Filter filter_highbeta(highbeta, oldhighbeta, 2'b01, highbeta1);
  Filter filter_lowgamma(lowgamma, oldlowgamma, 2'b10, lowgamma1);
  
  always @(posedge Bus2IP_Clk)
	  begin
		  // && oldlowbeta<=32'h0000_891D
		  if(oldlowbeta>=32'h0000_21A9)
			 slv_reg6 = lowbeta_result;
		  else
			 slv_reg6 = slv_reg0;
		  // && oldhighbeta<=32'h0000_79A0
		  if(oldhighbeta>=32'h0000_1AC2)
			 slv_reg7 = highbeta_result;
		  else
			 slv_reg7 = slv_reg1;
		  // && oldlowgamma<=32'h0000_4301
		  if(oldlowgamma>=32'h0000_0D8B)
			 slv_reg8 = lowgamma_result;
		  else
			 slv_reg8 = slv_reg3;
		  slv_reg9 = 32'h0000_0000;
		  if((lowbeta_result >= 32'h0000_21A9)&&(lowbeta_result <= 32'h0000_3224))
			 slv_reg9 = slv_reg9 + 32'h0000_0001;
		  else if((lowbeta_result >=32'h0000_3869)&&(lowbeta_result <= 32'h0000_891D))
			 slv_reg9 = slv_reg9 + 32'h0001_0000;
		  if((highbeta_result >= 32'h0000_1AC2)&&(highbeta_result <= 32'h0000_2DF9))
			 slv_reg9 = slv_reg9 + 32'h0000_0001;
		  else if((highbeta_result >= 32'h0000_2FA3)&&(highbeta_result <= 32'h0000_79A0))
			 slv_reg9 = slv_reg9 + 32'h0001_0000;
		  if((lowgamma_result >= 32'h0000_0D8B)&&(lowgamma_result <= 32'h0000_1D4A))
			 slv_reg9 = slv_reg9 + 32'h0000_0001;
		  else if((lowgamma_result >= 32'h0000_1EC4)&&(lowgamma_result <= 32'h0000_4301))
			 slv_reg9 = slv_reg9 + 32'h0001_0000;
		  
		  if((knn_value >= 32'h0002_0001)&&(attention > 32'h0000_0032))
			 slv_reg10 = 32'h0000_0000;
		  else if((knn_value >= 32'h0002_0001)&&(attention <= 32'h0000_0032))
			 slv_reg10 = 32'h0000_0001;
		  else
			 slv_reg10 = 32'h0000_0002;
		  /*if(slv_reg9 <= 32'h0001_0002)
		    slv_reg10 = 32'h0000_0002;
		  else if(slv_reg4 > 32'h0000_0032)
			 slv_reg10 = 32'h0000_0000;
		  else
			 slv_reg10 = 32'h0000_0001;*/
	  end
  // ------------------------------------------------------
  // Example code to read/write user logic slave model s/w accessible registers
  // 
  // Note:
  // The example code presented here is to show you one way of reading/writing
  // software accessible registers implemented in the user logic slave model.
  // Each bit of the Bus2IP_WrCE/Bus2IP_RdCE signals is configured to correspond
  // to one software accessible register by the top level template. For example,
  // if you have four 32 bit software accessible registers in the user logic,
  // you are basically operating on the following memory mapped registers:
  // 
  //    Bus2IP_WrCE/Bus2IP_RdCE   Memory Mapped Register
  //                     "1000"   C_BASEADDR + 0x0
  //                     "0100"   C_BASEADDR + 0x4
  //                     "0010"   C_BASEADDR + 0x8
  //                     "0001"   C_BASEADDR + 0xC
  // 
  // ------------------------------------------------------

  assign
    slv_reg_write_sel = Bus2IP_WrCE[10:0],
    slv_reg_read_sel  = Bus2IP_RdCE[10:0],
    slv_write_ack     = Bus2IP_WrCE[0] || Bus2IP_WrCE[1] || Bus2IP_WrCE[2] || Bus2IP_WrCE[3] || Bus2IP_WrCE[4] || Bus2IP_WrCE[5] || Bus2IP_WrCE[6] || Bus2IP_WrCE[7] || Bus2IP_WrCE[8] || Bus2IP_WrCE[9] || Bus2IP_WrCE[10],
    slv_read_ack      = Bus2IP_RdCE[0] || Bus2IP_RdCE[1] || Bus2IP_RdCE[2] || Bus2IP_RdCE[3] || Bus2IP_RdCE[4] || Bus2IP_RdCE[5] || Bus2IP_RdCE[6] || Bus2IP_RdCE[7] || Bus2IP_RdCE[8] || Bus2IP_RdCE[9] || Bus2IP_RdCE[10];

  // implement slave model register(s)
  always @( posedge Bus2IP_Clk )
    begin

      if ( Bus2IP_Resetn == 1'b0 )
        begin
          slv_reg0 <= 0;
          slv_reg1 <= 0;
          //slv_reg2 <= 0;
          slv_reg3 <= 0;
          slv_reg4 <= 0;
          slv_reg5 <= 0;
          /*slv_reg6 <= 0;
          slv_reg7 <= 0;
          slv_reg8 <= 0;
          slv_reg9 <= 0;
          slv_reg10 <= 0;*/
        end
      else
        case ( slv_reg_write_sel )
          11'b10000000000 :
            for ( byte_index = 0; byte_index <= (C_SLV_DWIDTH/8)-1; byte_index = byte_index+1 )
              if ( Bus2IP_BE[byte_index] == 1 )
                slv_reg0[(byte_index*8) +: 8] <= Bus2IP_Data[(byte_index*8) +: 8];
          11'b01000000000 :
            for ( byte_index = 0; byte_index <= (C_SLV_DWIDTH/8)-1; byte_index = byte_index+1 )
              if ( Bus2IP_BE[byte_index] == 1 )
                slv_reg1[(byte_index*8) +: 8] <= Bus2IP_Data[(byte_index*8) +: 8];
          /*11'b00100000000 :
            for ( byte_index = 0; byte_index <= (C_SLV_DWIDTH/8)-1; byte_index = byte_index+1 )
              if ( Bus2IP_BE[byte_index] == 1 )
                slv_reg2[(byte_index*8) +: 8] <= Bus2IP_Data[(byte_index*8) +: 8];*/
          11'b00010000000 :
            for ( byte_index = 0; byte_index <= (C_SLV_DWIDTH/8)-1; byte_index = byte_index+1 )
              if ( Bus2IP_BE[byte_index] == 1 )
                slv_reg3[(byte_index*8) +: 8] <= Bus2IP_Data[(byte_index*8) +: 8];
          11'b00001000000 :
            for ( byte_index = 0; byte_index <= (C_SLV_DWIDTH/8)-1; byte_index = byte_index+1 )
              if ( Bus2IP_BE[byte_index] == 1 )
                slv_reg4[(byte_index*8) +: 8] <= Bus2IP_Data[(byte_index*8) +: 8];
          11'b00000100000 :
            for ( byte_index = 0; byte_index <= (C_SLV_DWIDTH/8)-1; byte_index = byte_index+1 )
              if ( Bus2IP_BE[byte_index] == 1 )
                slv_reg5[(byte_index*8) +: 8] <= Bus2IP_Data[(byte_index*8) +: 8];
          /*11'b00000010000 :
            for ( byte_index = 0; byte_index <= (C_SLV_DWIDTH/8)-1; byte_index = byte_index+1 )
              if ( Bus2IP_BE[byte_index] == 1 )
                slv_reg6[(byte_index*8) +: 8] <= Bus2IP_Data[(byte_index*8) +: 8];
          11'b00000001000 :
            for ( byte_index = 0; byte_index <= (C_SLV_DWIDTH/8)-1; byte_index = byte_index+1 )
              if ( Bus2IP_BE[byte_index] == 1 )
                slv_reg7[(byte_index*8) +: 8] <= Bus2IP_Data[(byte_index*8) +: 8];
          11'b00000000100 :
            for ( byte_index = 0; byte_index <= (C_SLV_DWIDTH/8)-1; byte_index = byte_index+1 )
              if ( Bus2IP_BE[byte_index] == 1 )
                slv_reg8[(byte_index*8) +: 8] <= Bus2IP_Data[(byte_index*8) +: 8];
          11'b00000000010 :
            for ( byte_index = 0; byte_index <= (C_SLV_DWIDTH/8)-1; byte_index = byte_index+1 )
              if ( Bus2IP_BE[byte_index] == 1 )
                slv_reg9[(byte_index*8) +: 8] <= Bus2IP_Data[(byte_index*8) +: 8];
          11'b00000000001 :
            for ( byte_index = 0; byte_index <= (C_SLV_DWIDTH/8)-1; byte_index = byte_index+1 )
              if ( Bus2IP_BE[byte_index] == 1 )
                slv_reg10[(byte_index*8) +: 8] <= Bus2IP_Data[(byte_index*8) +: 8];*/
          default : begin
            slv_reg0 <= slv_reg0;
            slv_reg1 <= slv_reg1;
            //slv_reg2 <= slv_reg2;
            slv_reg3 <= slv_reg3;
            slv_reg4 <= slv_reg4;
            slv_reg5 <= slv_reg5;
            /*slv_reg6 <= slv_reg6;
            slv_reg7 <= slv_reg7;
            slv_reg8 <= slv_reg8;
            slv_reg9 <= slv_reg9;
            slv_reg10 <= slv_reg10;*/
                    end
        endcase

    end // SLAVE_REG_WRITE_PROC

  // implement slave model register read mux
  always @( slv_reg_read_sel or slv_reg0 or slv_reg1 or slv_reg2 or slv_reg3 or slv_reg4 or slv_reg5 or slv_reg6 or slv_reg7 or slv_reg8 or slv_reg9 or slv_reg10 )
    begin 

      case ( slv_reg_read_sel )
        11'b10000000000 : slv_ip2bus_data <= slv_reg0;
        11'b01000000000 : slv_ip2bus_data <= slv_reg1;
        11'b00100000000 : slv_ip2bus_data <= slv_reg2;
        11'b00010000000 : slv_ip2bus_data <= slv_reg3;
        11'b00001000000 : slv_ip2bus_data <= slv_reg4;
        11'b00000100000 : slv_ip2bus_data <= slv_reg5;
        11'b00000010000 : slv_ip2bus_data <= slv_reg6;
        11'b00000001000 : slv_ip2bus_data <= slv_reg7;
        11'b00000000100 : slv_ip2bus_data <= slv_reg8;
        11'b00000000010 : slv_ip2bus_data <= slv_reg9;
        11'b00000000001 : slv_ip2bus_data <= slv_reg10;
        default : slv_ip2bus_data <= 0;
      endcase

    end // SLAVE_REG_READ_PROC

  // ------------------------------------------------------------
  // Example code to drive IP to Bus signals
  // ------------------------------------------------------------

assign IP2Bus_Data = (slv_read_ack == 1'b1) ? slv_ip2bus_data :  0 ;
  assign IP2Bus_WrAck = slv_write_ack;
  assign IP2Bus_RdAck = slv_read_ack;
  assign IP2Bus_Error = 0;

endmodule

module Filter
(
	input [31:0] data,
	input [31:0] old,
	input [1:0] Filterop,
	output [31:0] result
);

reg [31:0] temp;
assign result = temp;

always
begin 
	case(Filterop)
		//lowbeta
		2'b00:
			if((data < 32'h0000_21A9)||(data > 32'h0000_891D))
				temp = old;
			else
				temp = data;
		//highbeta
		2'b01:
			if((data < 32'h0000_1AC2)||(data > 32'h0000_79A0))
				temp = old;
			else
				temp = data;
		//lowgamma
		2'b10:
			if((data < 32'h0000_0D8B)||(data > 32'h0000_4301))
				temp = old;
			else 
				temp = data;
	endcase
end

endmodule
