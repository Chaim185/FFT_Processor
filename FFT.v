module FFT (input wire [3:0] x_in0, input wire [3:0] x_in1, input wire [3:0] x_in2, input wire [3:0] x_in3,
				input wire [3:0] x_in4, input wire [3:0] x_in5, input wire [3:0] x_in6, input wire [3:0] x_in7,
				input wire Clock, input wire Reset,
output reg [25:0] X_out0, output reg [25:0] X_out1, output reg [25:0] X_out2, output reg [25:0] X_out3,
output reg [25:0] X_out4, output reg [25:0] X_out5, output reg [25:0] X_out6, output reg [25:0] X_out7);
					
	// In order for the Cooley-Tukey algorithm to work correctly, WN = e^(-j2pi/N), a complex number
	// with reals (floats) as its real and imaginary parts. However, in the interest of simplifying the 
	// project, WN is an integer
				
	integer W2 = 16; // This is the coefficient for the value N = 2. (WN)^2 = W(N/2)
						 // so WN will change as N changes.
	integer W4 = 4; 
	integer W8 = 2;
	integer i; // to be used in for loops

// FFT input variables are lowercase. Output vairables are capitalized
	
	reg [3:0] x [0:7]; // This is in place of input wires. I'm using it because Verilog won't allow 2-D arrays
							  //for I/O ports
							  
	reg [3:0] y [0:3];
	reg [3:0] z [0:3];

	reg [3:0] y$ [0:1];
	reg [3:0] y$$ [0:1];
	reg [3:0] z$ [0:1];
	reg [3:0] z$$ [0:1];
	
	reg [3:0] a,b,c,d,e,f,g,h;
							  
	reg [25:0] A,B,C,D,E,F,G,H; // Since FFT output has adders and multipliers, they must contain more bits
	
	reg [25:0] Y$ [0:1];
	reg [25:0] Y$$ [0:1];
	reg [25:0] Z$ [0:1];
	reg [25:0] Z$$ [0:1];
	
	reg [25:0] Y [0:3];
	reg [25:0] Z [0:3];
	
	reg [25:0] X [0:7];
	





	always @ (posedge Clock or negedge Reset)
		begin
			if (!Reset)
				begin
					// There is no signal interdependency so use non-blocking assignments
					X_out0 <= 'b0000;
					X_out1 <= 'b0000;
					X_out2 <= 'b0000;
					X_out3 <= 'b0000;
					X_out4 <= 'b0000;
					X_out5 <= 'b0000;
					X_out6 <= 'b0000;
					X_out7 <= 'b0000;
				end
			else 
				begin			
					// Each stage is dependent on the previous stage, so use blocking assignments
					x[0] = x_in0;
					x[1] = x_in1;
					x[2] = x_in2;
					x[3] = x_in3;
					x[4] = x_in4;
					x[5] = x_in5;
					x[6] = x_in6;
					x[7] = x_in7;
			
						
					for (i=0; i<8; i=i+2)
						y[i/2] = x[i];
						
					for (i=1; i<8; i=i+2)		
						z[(i-1)/2] = x[i];	
						
					
					for (i=0; i<4; i=i+2)
						begin
							y$[i/2] = y[i];
							z$[i/2] = z[i];
						end	
			
					for (i=1; i<4; i=i+2)
						begin
							y$$[(i-1)/2] = y[i];
							z$$[(i-1)/2] = z[i];
						end
						
						
						
					a = y$[0];
					b = y$[1];
					c = y$$[0];
					d = y$$[1];
					e = z$[0];
					f = z$[1];
					g = z$$[0];
					h = z$$[1];
			
			
			
					A = a;
					B = b;
					C = c;
					D = d;
					E = e;
					F = f;
					G = g;
					H = h;
			
					

					for (i=0; i<2; i=i+1)
						begin
							Y$[i] = A + B*(W2**i);
							Y$$[i] = C + D*(W2**i);
							Z$[i] = E + F*(W2**i);
							Z$$[i] = G + H*(W2**i);
						end

			
			
			
			
					for (i=0; i<4; i=i+1)
						begin
							if (i<2)
								begin
									Y[i] = Y$[i] + Y$$[i]*(W4**i); 
									Z[i] = Z$[i] + Z$$[i]*(W4**i);
								end
							else
								begin
									Y[i] = Y$[i-2] + Y$$[i-2]*(W4**i); 
									Z[i] = Z$[i-2] + Z$$[i-2]*(W4**i);
								end
						end
			
			

			
					for (i=0; i<8; i=i+1)
						begin
							if (i<4)
								X[i] = Y[i] + Z[i]*(W8**i);
							else
								X[i] = Y[i-4] + Z[i-4]*(W8**i); 
						end
			
		
		
				/*for (i=0; i<8; i=i+1) // for debugging 
					 begin
						if (i<4)
							X[i] = W8**i;
						else
							X[i] = W8**(i+18); // Verilog won't return values of sych high powers even though
													 // X is 26 bits long. Perhaps this requires a computer with more RAM
					 end	
				*/

					X_out0 = X[0];
					X_out1 = X[1];
					X_out2 = X[2];
					X_out3 = X[3];
					X_out4 = X[4];
					X_out5 = X[5];
					X_out6 = X[6];
					X_out7 = X[7];
				end
		end
		
endmodule
