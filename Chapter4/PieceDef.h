#pragma once
//����


enum class TYPE { G, R, H, C, NO };//G��˧�򽫣�R�ǳ���H����C����,NO��ʾû������
struct Piece //����
{
	static int realRedNum;
	static Piece* blackG;
	static Piece* redPieces;

	static void initGame(Piece* blackG, Piece redPieces[],int realRedNum)//��ʼ�����
	{
		if (Piece::blackG != nullptr)
		{
			delete Piece::blackG;
			Piece::blackG = nullptr;
		}
		Piece::blackG = blackG;
		Piece::realRedNum = realRedNum;
		if (Piece::redPieces != nullptr)
		{
			delete[] Piece::redPieces;
			Piece::redPieces = nullptr;
		}
		Piece::redPieces = new Piece[realRedNum];
		for (int i = 0; i < Piece::realRedNum; i++)
		{
			Piece::redPieces[i] = redPieces[i];
		}
	}

	static bool redWin()//�췽�Ƿ�Ѻڷ�������
	{
		for (int i = 0; i < realRedNum; i++)//���ڽ��ܷ�Ժ�˧��������ԣ�����false
		{
			if (redPieces[i].type == TYPE::G)
			{
				if (blackG->eat(redPieces[i])) return false;
			}
		}
		if (blackG->y - 1 >= 4)
		{
			blackG->y -= 1;
			bool canSurvive = true;//�ڽ�����һ���Ƿ��ܴ��
			for (int i = 0; i < realRedNum; i++)
			{
				if (redPieces[i].eat(*blackG))
				{
					canSurvive = false;
					break;
				}
			}
			if (canSurvive) return false;
			blackG->y += 1;
		}
		if (blackG->y + 1 <= 6)
		{
			blackG->y += 1;
			bool canSurvive = true;//�ڽ�����һ���Ƿ��ܴ��
			for (int i = 0; i < realRedNum; i++)
			{
				if (redPieces[i].eat(*blackG))
				{
					canSurvive = false;
					break;
				}
			}
			if (canSurvive) return false;
			blackG->y -= 1;
		}
		if (blackG->x - 1 >= 1)
		{
			blackG->x -= 1;
			bool canSurvive = true;//�ڽ�����һ���Ƿ��ܴ��
			for (int i = 0; i < realRedNum; i++)
			{
				if (redPieces[i].eat(*blackG))
				{
					canSurvive = false;
					break;
				}
			}
			if (canSurvive) return false;
			blackG->x += 1;
		}
		if (blackG->x + 1 <= 10)
		{
			blackG->x += 1;
			bool canSurvive = true;//�ڽ�����һ���Ƿ��ܴ��
			for (int i = 0; i < realRedNum; i++)
			{
				if (redPieces[i].eat(*blackG))
				{
					canSurvive = false;
					break;
				}
			}
			if (canSurvive) return false;
			blackG->x -= 1;
		}
		return true;//�����߷������ܴ�������
	}
	int x;
	int y;
	TYPE type;
	bool isRed;//�Ƿ��Ǻ췽����
	Piece(int x, int y, TYPE type, bool isRed)
	{
		this->x = x;
		this->y = y;
		this->type = type;
		this->isRed = isRed;
	}
	Piece()
	{
		this->x = 0;
		this->y = 0;
		this->type = TYPE::NO;
		this->isRed = true;
	}
	Piece(int x, int y)
	{
		this->x = x;
		this->y = y;
		this->type = TYPE::NO;
		this->isRed = true;
	}
	bool eat(Piece piece)//this.piece�ܷ�Ե�piece
	{
		switch (type)
		{
		case TYPE::G:
			return G_to(piece);
		case TYPE::R:
			return R_to(piece);
		case TYPE::H:
			return H_to(piece);
		case TYPE::C:
			return C_to(piece);
		case TYPE::NO:
			return false;
		}
	}
	bool valid() { return this->type != TYPE::NO; }
	int pieceNumBetween(Piece piece)//������������֮���ж�������,����������Ӳ���һ��ֱ���ϣ�����-1���������ͬ�����ӣ�����-1,piece��this������No���͵�����
	{
		if (this->theSameAs(piece)) return -1;
		int dx = x - piece.x;
		int dy = y - piece.y;
		if (dx != 0 && dy != 0) return -1;//�����ߣ��򷵻�-1
		if (dx == 0)
		{
			int num = 0;
			int maxY = y > piece.y ? y : piece.y;
			int minY = y > piece.y ? piece.y : y;
			if (!theSameAs(*blackG) && minY<blackG->y && maxY >blackG->y)
			{
				num++;
			}
			for (int i = 0; i < realRedNum; i++)
			{
				if (!theSameAs(redPieces[i]) && redPieces[i].x == x && minY<redPieces[i].y && maxY >redPieces[i].y)
				{
					num++;
				}
			}
			return num;
		}
		else if (dy == 0)
		{
			int num = 0;
			int maxX = x > piece.x ? x : piece.x;
			int minX = x > piece.x ? piece.x : x;
			if (!theSameAs(*blackG) && minX<blackG->x && maxX >blackG->x)
			{
				num++;
			}
			for (int i = 0; i < realRedNum; i++)
			{
				if (!theSameAs(redPieces[i]) && redPieces[i].y == y && minX<redPieces[i].x && maxX >redPieces[i].x)
				{
					num++;
				}
			}
			return num;
		}
		else
		{
			return -1;
		}
	}

	bool theSameAs(Piece piece)
	{
		return this->x == piece.x && this->y == piece.y && this->type == piece.type && this->isRed == piece.isRed;
	}

	bool H_to(Piece toPiece)//�����piece�����򷵻��ܷ��toPiece��λ�ã�������������
	{
		if (isRed == toPiece.isRed) return false;
		if (distance(toPiece) != 3) return false;
		int dx = (x - toPiece.x) & 0x7FFFFFFF;
		int dy = (y - toPiece.y) & 0x7FFFFFFF;
		if (dx == 0 || dy == 0) return false;
		if (dx == 1)
		{
			Piece tPiece = Piece(x, toPiece.y);
			return pieceNumBetween(tPiece) != 1;
		}
		else// dx = 2
		{
			Piece tPiece = Piece(toPiece.x, y);
			return pieceNumBetween(tPiece) != 1;
		}
	}

	bool R_to(Piece toPiece)//�����piece�ǳ����򷵻��ܷ��toPiece��λ��
	{
		if (isRed == toPiece.isRed) return false;
		return pieceNumBetween(toPiece) == 0;
	}

	bool C_to(Piece toPiece)//�����piece���ڣ��򷵻��ܷ��toPiece��λ��
	{
		if (isRed == toPiece.isRed) return false;
		return pieceNumBetween(toPiece) == 1;
	}

	bool G_to(Piece toPiece)//�����piece��˧�򽫣��򷵻��ܷ��toPiece��λ��
	{
		if (isRed == toPiece.isRed) return false;
		if (toPiece.type == TYPE::G) return pieceNumBetween(toPiece) == 0;
		if (distance(toPiece) == 1)//Ĭ�Ϻڽ����Ϸ�
		{
			if (isRed)//�췽
			{
				return toPiece.x >= 4 && toPiece.x <= 6 && toPiece.y >= 8 && toPiece.y <= 10;//��֤toPiece�ھŹ�����
			}
			else//�ڷ�
			{
				return toPiece.x >= 4 && toPiece.x <= 6 && toPiece.y >= 1 && toPiece.y <= 3;
			}
		}
		else if (toPiece.type == TYPE::G && pieceNumBetween(toPiece) == 0)
			return true;
		else
			return false;
	}

	int distance(Piece piece)//������������֮��x�ľ�����y�ľ���֮��
	{
		int dx = x - piece.x;
		int dy = y - piece.y;
		return dx & 0x7FFFFFFF + dy & 0x7FFFFFFF;
	}
};

