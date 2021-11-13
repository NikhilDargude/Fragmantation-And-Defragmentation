//************************
// Defragmentation
//************************

#include<stdio.h>
#include<malloc.h>

//*************************************************************
//    	***	User Define structure ****
// 
//		first & Last Data Members are self referential pointer. 
//		Second is normal integer Number, 
//*************************************************************

struct node
{
	struct node* pPrev;
	int iData;
	struct node* pNext;
};

void Defragment(struct node**, struct node**);
void Create(struct node**, struct node**, int);
void Insert(struct node**, struct node**, int);
void Remove(struct node**, struct node**);
void Display(struct node*, struct node*);
int Counte(struct node*, struct node*);
int Delete(struct node**, int);

int main(void)
{
	int iNo;
	int iDel;
	int iPos;
	int iCount;
	int iYes = 1;
	int iState = 0;  // How many node are empty. give status.
	int iChoice = 0;
	struct node* pFirst = NULL;
	struct node* pLast = NULL;

	Create(&pFirst, &pLast, 5);

	while (iYes)
	{
		printf("\n1-Insert\n2-Delete\n3-Defragment\n4-Exit");
		printf("\nEnter Your Choice:-\t");
		scanf_s("%d", &iChoice);

		switch (iChoice)
		{
		case 1:
			if (iState < 5)
			{
				printf("\nEnter Your Data too Insert:-\t");
				scanf_s("%d", &iNo);

				Insert(&pFirst, &pLast, iNo);

				iState++;

				Display(pFirst, pLast);
			}
			else
			{
				printf("\nLinked List Is Full\n");
				Display(pFirst, pLast);
			}

			break;

		case 2:
			if (iState > 0)
			{
				printf("\nEnter Your Possion To Delete node:-\t");
				scanf_s("%d", &iPos);


				iCount = Counte(pFirst, pLast);

				if (iPos > (iCount + 1))
					printf("\nPOSSION IS INVALID");
				else
				{
					iDel = Delete(&pFirst, iPos);

					if (iDel != -1)
					{
						if (iDel == 0)
							printf("\nNode Allredy Deleted\n");
						else
							printf("Deleted Node is %d \n", iDel);

						if (iDel != 0)
						{
							iState--;
						}

						Display(pFirst, pLast);
					}
				}
			}
			else
			{
				printf("\nLinked List Is Empty\n");
				Display(pFirst, pLast);
			}

			break;

		case 3:
			Defragment(&pFirst, &pLast);
			Display(pFirst, pLast);
			break;

		case 4:
			iYes = 0;
			break;

		default:
			printf("INVALID CHOICE\n");

		}
	}

	Remove(&pFirst, &pLast);
}

//***********************************************************
// 
//  Name :  Delete
// 
//  Parameters : 
// 		[IN / OUT] struct node ** ppHead :
//     		 Input will be address of structure object and objetc having self referential pointer. 
//
// 		[IN]  int iPos : 
// 			Thise parameter willint SearchFirstOccurrence(struct node *, struct node *, int); contain Position of Delete node Data to be.
//
//		Note - thise function well Delete node data and update Linked list.
//*****************************************************************

int Delete(struct node** ppHead, int iPos)
{
	int iDel;
	int iCount = 1;

	struct node* pTemp = (*ppHead);

	if (iPos <= 0)
	{
		printf("Invalid possion\n");
		return -1;
	}

	while (iCount != iPos)
	{
		pTemp = pTemp->pNext;
		iCount++;
	}

	if (pTemp->iData == 0)
		return 0;
	else
	{
		iDel = pTemp->iData;
		pTemp->iData = 0;
	}

	return iDel;
}

//***********************************************************
// 
//  Name :  Insert
// 
//  Parameters : 
// 		[IN / OUT] struct node ** ppHead :
//     		 Input will be address of structure object and objetc having self referential pointer, 
//
// 		[IN]  int iNo : 
// 			Thise parameter will contain Data to be insert in  node.
//
//		Note -: thise function will update liked list. inserting data.
//*******************************************************************

void Insert(struct node** ppHead, struct node** ppTail, int iNo)
{
	struct node* pTemp = *ppHead;

	do
	{
		if ((pTemp)->iData == 0)
		{
			(pTemp)->iData = iNo;
			break;
		}
		(pTemp) = (pTemp)->pNext;

	} while (*ppHead != (pTemp));
}


//***********************************************************
// 
//  Name :  Create
// 
//  Parameters : 
// 		[IN / OUT] struct node ** ppHead :
//     		 Input will be address of structure object and objetc having self referential pointer.
//              pointing to linked list first node.
//
// 		[IN / OUT] struct node ** ppTail :
//     		 Input will be address of structure object and objetc having self referential pointer.
//             pointing to linked list last node.
//
// 		[IN]  int iNum : 
// 			Thise parameter will contain count of creating node.
//
//		Note -: thise function will create linked list of and insert data 0 .
//*******************************************************************

void Create(struct node** ppHead, struct node** ppTail, int iNum)
{
	int iNo = 0;

	while (iNo != iNum)
	{
		struct node* pNewnode = NULL;

		pNewnode = (struct node*)malloc(sizeof(struct node));
		if (NULL == pNewnode)
		{
			printf("\n Memory allocation is Faild\n");
			return;
		}
		pNewnode->iData = 0;

		if (NULL == (*ppHead))
		{
			pNewnode->pNext = pNewnode;
			pNewnode->pPrev = pNewnode;
			(*ppHead) = pNewnode;
		}
		else
		{
			(*ppTail)->pNext = pNewnode;
			pNewnode->pPrev = (*ppTail);
			pNewnode->pNext = (*ppHead);
			(*ppHead)->pPrev = pNewnode;
		}
		(*ppTail) = pNewnode;
		iNo++;
	}
}

//***********************************************************
// 
//  Name :  Remove
// 
//  Parameters : 
// 		[IN / OUT] struct node ** ppHead :
//     		 Input will be address of structure object and objetc having self referential pointer. 
//  		
// 		[IN / OUT] struct node ** ppTail :
//     		 Input will be address of structure object and objetc having self referential pointer.

//		Note -: thise function will free created Liked list.
//*******************************************************************

void Remove(struct node** ppHead, struct node** ppTail)
{
	struct node* pTemp = *ppHead;

	if (*ppHead == NULL)
		return;

	while ((*ppHead) != (*ppTail))
	{
		*ppHead = pTemp->pNext;
		pTemp->pNext = NULL;
		pTemp->pPrev = NULL;
		free(pTemp);
		pTemp = (*ppHead);
	}

	if ((*ppHead) == (*ppTail))
	{
		(*ppHead)->pNext = NULL;
		(*ppHead)->pPrev = NULL;
	}

	*ppHead = *ppTail = pTemp = NULL;
}


//***********************************************************
// 
//  Name :  Defragment
// 
//  Parameters : 
// 		[IN / OUT] struct node ** ppHead :
//     		 Input will be address of structure object and objetc having self referential pointer. 
//  		
// 		[IN / OUT] struct node ** ppTail :
//     		 Input will be address of structure object and objetc having self referential pointer.

//		Note -: thise function Manipulat data;
//*******************************************************************

void Defragment(struct node** ppHead, struct node** ppTail)
{
	struct node* pTemp1 = (*ppTail);
	struct node* pTemp2 = NULL;

	do
	{
		if (pTemp1->iData == 0)
		{
			pTemp2 = pTemp1;

			do
			{
				if (pTemp2->iData != 0)
				{
					pTemp1->iData = pTemp2->iData;
					pTemp2->iData = 0;
					break;
				}
				pTemp2 = pTemp2->pPrev;
			} while (pTemp2 != (*ppTail));
		}

		pTemp1 = pTemp1->pPrev;
	} while (pTemp1 != (*ppTail));
}

//***********************************************************
// 
//  Name :  Display
// 
//  Parameters : 
// 		[IN] struct node * pHead :
//     		 Input will be address of structure object and objetc are self referential pointer, 
//  			Accept in *pHead.
//
// 		[IN] struct node * pTail :
//     		 Input will be address of structure object and objetc are self referential pointer, 
//  			Accept in *pTail.
//
//		Note -: thise function will Print all liked list.
//*******************************************************************

void Display(struct node* pHead, struct node* pTail)
{
	if (pHead == NULL)
	{
		printf("Linked List Is Empty");
		return;
	}

	do
	{
		printf("|%d|->", pHead->iData);
		pHead = pHead->pNext;

	} while (pHead->pPrev != pTail);

	printf("\n");
}

//***********************************************************
// 
//  Name :  Counte
// 
//  Parameters : 
// 		[IN] struct node * ppHead :
//     		 Input will be address of structure object and objetc having self referential pointer.
//
// 		[IN / OUT] struct node ** ppHead :
//     		 Input will be address of structure object and objetc having self referential pointer. 
//
//		Note -: thise function will return Conut of presendted node.
//*******************************************************************

int Counte(struct node* pHead, struct node* pTail)
{
	int iCount = 0;

	if (pHead == NULL)
		printf("\nMemory Allocation is FAILD");
	else
	{
		do
		{
			iCount++;
			pHead = pHead->pNext;
		} while (pHead->pPrev != pTail);
	}
	return iCount;
}
