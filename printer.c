#pragma config(Motor,  motorA,          x_motor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          y_motor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          z_motor,    tmotorEV3_Medium, PIDControl, encoder)

void HexToBinStr(unsigned char* hexStr, unsigned char* binStr, int lenHex)
{
    memset(binStr, '0', lenHex * 8);
    unsigned char hexChar[2];
    for(int i = 0; i < lenHex; i++)
    {
        hexChar[0] = (hexStr[i] & 0xF0) >> 4;
        hexChar[1] = hexStr[i] & 0x0F;
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                if(hexChar[j] & (0x08 >> k))
                {
                    binStr[8 * i + 4 * j + k] = '1';
                }
            }           
        }
    }
}   



task main()
{
	unsigned char bin[257];
	int i;
	unsigned char bits[32]=
	{
	0x00,0x00,0x00,0x40,0x00,0x40,0x7E,0x40,0x08,0x7C,0x08,0x88,0x09,0x48,0x28,0x48,
    0x2E,0x48,0x28,0x50,0x28,0x50,0x28,0x20,0x2E,0x50,0x70,0x88,0x01,0x04,0x00,0x00,
	};
	HexToBinStr(bits, bin, 32);
	
    while(true)
    {
        for(i=0;i<256;i++)
        {
            if(i%16==0&&i!=0)
            {
                resetMotorEncoder(y_motor);
                setMotorTarget(y_motor, 10, 50);
                waitUntilMotorStop(y_motor);
                resetMotorEncoder(x_motor);
                setMotorTarget(x_motor, 15*16, -50);
                waitUntilMotorStop(x_motor);
            }
            if(bin[i]=='1')
            {
                resetMotorEncoder(z_motor);
                setMotorTarget(z_motor, 90, 50);
                waitUntilMotorStop(z_motor);
                resetMotorEncoder(z_motor);
                setMotorTarget(z_motor, 90, -50);
                waitUntilMotorStop(z_motor);
                sleep(1000);
            }
            resetMotorEncoder(x_motor);
            setMotorTarget(x_motor, 15, 50);
            waitUntilMotorStop(x_motor);
        }
        if(i==256)
        {
            break;
        }
    }
}
