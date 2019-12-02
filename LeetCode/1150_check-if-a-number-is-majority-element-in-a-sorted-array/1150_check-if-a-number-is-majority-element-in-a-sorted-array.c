
bool isMajorityElement(int* nums, int numsSize, int target)
{
	    int times = numsSize/2 + 1;
		    int ctr = 0;
			    for (int i = 0; i < numsSize; i++)
					    {
							        if (target == nums[i])
										        {
													            ctr++;
																        }
									    }
				    
				    return ctr >= times;
}


