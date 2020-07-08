#include "waterdrop.h"

void	aff_meta(meta_t *meta)
{
	printf("sR : %s\n", meta->strR);
	printf("R  : ww : %d : wh  : %d\n", meta->WW, meta->WH);
	printf("NO : %s\n", meta->pathN);
	printf("SO : %s\n", meta->pathS);
	printf("EA : %s\n", meta->pathE);
	printf("WE : %s\n", meta->pathW);
	printf("SP : %s\n", meta->pathSP);
	printf("F  : %s\n", meta->pathF);
	printf("C  : %s\n", meta->pathR);
}

meta_t	*meta_init(void)
{
	meta_t *meta;

	if (!(meta = malloc(sizeof(meta_t))))
	{
		printf("Error\nNo memory for meta datas\n");
		return (NULL);
	}
	meta->WW = 0;
 	meta->WH = 0;
	meta->strR = NULL;
	meta->pathN = NULL;
	meta->pathS = NULL;
	meta->pathE = NULL;
	meta->pathW = NULL;
	meta->pathSP = NULL;
	meta->pathF = NULL;
	meta->pathR = NULL;

	return (meta);
}

void	remove_meta(meta_t **m)
{
	if (!*m)
		return ;
	if ((*m)->strR)
		free((*m)->strR);
	if ((*m)->pathN)
		free((*m)->pathN);
	if ((*m)->pathS)
		free((*m)->pathS);
	if ((*m)->pathE)
		free((*m)->pathE);
	if ((*m)->pathW)
		free((*m)->pathW);
	if ((*m)->pathSP)
		free((*m)->pathSP);
	if ((*m)->pathF)
		free((*m)->pathF);
	if ((*m)->pathR)
		free((*m)->pathR);
	if ((*m))
		free(*m);
}