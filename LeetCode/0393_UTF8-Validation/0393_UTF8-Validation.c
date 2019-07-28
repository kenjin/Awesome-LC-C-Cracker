bool validUtf8(int* data, int dataSize)
{
	int groupCtr = 0;
	for (int i = 0; i < dataSize; i++)
	{
		// count the UTF group count
		if (0 == groupCtr)
		{
			int flag = (0x1 << 7);
			for (int x = 0; x < 8; x++)
			{
				if ((data[i] & flag) != flag)
				{
					break;            
				}
				groupCtr++;
				flag = (flag >> 1);
			}
			if ((groupCtr > 4) /* A character in UTF8 can be from 1 to 4 bytes */ ||  
					(groupCtr == 1) /* The 1st bit is 0 for 1-byte UTF character */ ) 
			{
				return false;
			}

			groupCtr = (groupCtr > 0 ? groupCtr-1 : groupCtr);            
		} else
		{
			// UTF character group validation
			if (!(data[i] & (0x1 << 7)) || (data[i] & (0x1 << 6)))
			{
				return false;            
			}
			groupCtr--;
		}
	}

	return (groupCtr > 0 ? false : true);
}

