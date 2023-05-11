#include <stdio.h>

#define INSTRUCTION 0xFC   // First 6 bits of MSb of MSB
#define MOV_INST 0x88     // First 6 bits of MSb of MSB
#define MOV_D 0x2    // D bit
#define MOV_W 0x1    // W bit
#define MOV_MOD 0xC0 // MOD bits
#define MOV_REG 0x38 // REG bits
#define MOV_RM 0x7   // RM bits

char wide_registers[8][3] = {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"};
char registers[8][3] = {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"};

int main()
{
	FILE *file = fopen("listing_37", "rb");
    char buffer[2];

	if(file)
	{
		FILE *answer_file = fopen("answer_37", "w");
		fputs("bits 16\n\n", answer_file);

		while(!feof(file))
		{
			buffer[0] = fgetc(file); // first byte
			buffer[1] = fgetc(file); // second byte

			if((buffer[0] & INSTRUCTION) == MOV_INST)
			{
				fputs("mov ", answer_file);

                char d_bit = buffer[0] & MOV_D;
                char w_bit = buffer[0] & MOV_W;
                char mod_bits = buffer[1] & MOV_MOD;
                char reg_bits = (buffer[1] & MOV_REG) >> 3;
                char rm_bits = buffer[1] & MOV_RM;

				if(d_bit == 0) // if the D bit is 0, REG is not the Destination; REG is source
				{

					for (int i = 0; i < 8; ++i)
					{

						 if (rm_bits == i)
                        {

                            if (w_bit != 0)
							{
								fputs(&wide_registers[i][0], answer_file);
							}

							else
							{
								fputs(&registers[i][0], answer_file);
							}

                            fputs(", ", answer_file);

                            for (int j = 0; j < 8; ++j)
                            {

                                if (reg_bits == j)
                                {
                                    if (w_bit != 0)
									{
										fputs(&wide_registers[j][0], answer_file);
									}

									else
									{
										fputs(&registers[j][0], answer_file);
									}
                                    break;
                                }
                            }

							fputs("\n", answer_file);

                        }
					}
				}
			}
		}

		fclose(answer_file);
		printf("Finished!");
	}
	
	else
	{
		printf("The file could not be opened or found!");
		return 1;
	}

	fclose(file);
	return 0;
}