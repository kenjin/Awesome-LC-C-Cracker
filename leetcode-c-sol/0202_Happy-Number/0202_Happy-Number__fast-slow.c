/**

  202. Happy Number [E]

  Write an algorithm to determine if a number is "happy".

  A happy number is a number defined by the following process: Starting
  with any positive integer, replace the number by the sum of the squares
  of its digits, and repeat the process until the number equals 1 (where
  it will stay), or it loops endlessly in a cycle which does not include
  1. Those numbers for which this process ends in 1 are happy numbers.

Example:

Input: 19
Output: true

Explanation:
1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1

*/

int checkHappy(int n)
{
	int target = n;

	int sum = (target%10)*(target%10);    
	// Chech digit
	while ( (target/10) > 0)
	{              
		target /= 10;
		sum += (target%10)*(target%10);
	}

	return sum;
}

bool isHappy(int n)
{
	int fast = n, slow = n;
	do
	{  
		/* slow calculate once per round*/
		slow = checkHappy(slow);
		/* fast calculate two times per round*/
		fast = checkHappy(fast);
		fast = checkHappy(fast);
		if (slow == 1 || fast == 1)
		{
			return true;
		}
	} while (slow != fast);  

	return  false;
}


