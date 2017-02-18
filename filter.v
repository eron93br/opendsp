`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:43:05 09/08/2016 
// Design Name: 
// Module Name:    filter 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////


module filter(filterdav, data_out, data_in, clock,
              x0, x1, x2, x3, x4, x5,
				  y0, y1, y2, y3, y4, y5
              );

parameter order = 5;
parameter word_size_in=12;
parameter word_size_out=2*word_size_in+2;

// INPUTs
input clock, filterdav;                         // System Clock 
input [word_size_in-1:0] data_in;    // 12-bits input from ADC..

// DECLARE OUTPUTs....
output reg [11:0] data_out;
output reg [11:0] x0, x1, x2, x3, x4, x5;
output reg [11:0] y0, y1, y2, y3, y4, y5;

integer k;
reg [11:0] a[0:order]; // X array
reg signed [word_size_out-1:0] y[0:order]; // Y array
reg [word_size_out-1:0] yn=0; 
 

   always @(posedge clock)
	begin
	   if(filterdav==1)
		begin
		for(k=0; k<=order; k=k+1)
		begin 
		  a[k]=0;
		  y[k]=0;
		end  
		end
		else
		begin
	   // --------------------------------
		a[0] = a[1];            // x[n-5] 
		a[1] = a[2];            // x[n-4] 
		a[2] = a[3];            // x[n-3] 
      a[3] = a[4];            // x[n-2] 
      a[4] = a[5];            // x[n-1] 
      a[5] = data_in;         // x[n] 
		// --------------------------------
	   y[0] = y[1];            // y[n-5] 
		y[1] = y[2];            // y[n-4] 
		y[2] = y[3];            // y[n-3] 
      y[3] = y[4];            // y[n-2] 
      y[4] = yn;              // y[n-1] 
      y[5] = a[5] + a[4] + a[3]; // y[n] 
      // --------------------------------
      // First TAP has only a register
		x0=a[0]; x1=a[1]; x2=a[2]; x3=a[3]; x4=a[4]; x5=a[5];
		y0=y[0]; y1=y[1]; y2=y[2]; y3=y[3]; y4=y[4]; y5=y[5];
     yn=y[5];
	  data_out = yn[11:0];
	  end
   end
 endmodule 
  
  
   
	
  
   
	

