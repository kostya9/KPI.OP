#define NOTHING -100
struct Move
{
	enum Ops m;
	int stance;
};
enum Ops { POP = -4, CONTINUE, REPEAT, BREAK };
int run(int moves[], int movesLen, int res[], int resLen)
{
	int resPos = 0;
	int movePos = 0;
	int i;

	
	int curStance = 0;
	struct Move mov[4][4];
	mov[0][0].m = 11;
	mov[0][0].stance = 1;
	mov[0][1].m = 55;
	mov[0][1].stance = 2;
	mov[0][2].m = 101;
	mov[0][2].stance = 3;
	mov[0][3].m = CONTINUE;
	mov[0][3].stance = 0;
	mov[1][0].m = NOTHING;
	mov[1][0].stance = NOTHING;
	mov[1][1].m = POP;
	mov[1][1].stance = 1;
	mov[1][2].m = 1;
	mov[1][2].stance = 2;
	mov[1][3].m = NOTHING;
	mov[1][3].stance = NOTHING;
	mov[2][0].m = POP;
	mov[2][0].stance = 0;
	mov[2][1].m = 5;
	mov[2][1].stance = 3;
	mov[2][2].m = REPEAT;
	mov[2][2].stance = 2;
	mov[2][3].m = 11;
	mov[2][3].stance = 2;
	mov[3][0].m = NOTHING;
	mov[3][0].stance = NOTHING;
	mov[3][1].m = NOTHING;
	mov[3][1].stance = NOTHING;
	mov[3][2].m = BREAK;
	mov[3][2].stance = NOTHING;
	mov[3][3].m = 2;
	mov[3][3].stance = 1;
	for (i = 0; i < movesLen; i++)
	{
		if (!move(res, resLen, &resPos, mov, moves[i], &curStance))
		{
			int n;
			for (n = resPos; n < resLen; n++)
				res[n] = 0;
			return resPos;
		}
		//@todo everything after resPos - 0;
	}
}
int move(int res[], int resLen, int * resPos, struct Move mov[4][4], int moveNum, int * curStance)
{
	struct Move currMov;
	switch (moveNum)
	{
		case 10:
		{
			currMov = mov[*curStance][0];
			curStance = currMov.stance;
		}
		break;
		case 18:
		{
			currMov = mov[*curStance][1];
		}
		break;
		case 28:
		{
			currMov = mov[*curStance][2];
		}
		break;
		case 208:
		{
			currMov = mov[*curStance][3];
		}
		break;
		default:
		{
			return 0;
		}
	}
	switch (currMov.m)
	{
		case POP:
		{
			if (resPos == 0)
				return 0;
			resPos--;
		}
		break;
		case CONTINUE:
		{
			return 1;
		}
		break;
		case REPEAT:
		{
			move(res, resLen, resPos, mov, moveNum, curStance);
		}
		break;
		case BREAK:
		{
			return 0;
		}
		break;
		case NOTHING:
		{
			return 0;
		}
		default:
		{
			(*resPos)++;
			res[*resPos] = currMov.m;
		}
	}
}