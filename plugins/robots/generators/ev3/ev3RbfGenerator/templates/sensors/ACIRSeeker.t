ARRAY8 ar@@RANDOM_ID_1@@ 4
ARRAY(CREATE8, 4, ar@@RANDOM_ID_1@@)
ARRAY_WRITE(ar@@RANDOM_ID_1@@, 0, 8)
ARRAY_WRITE(ar@@RANDOM_ID_1@@, 1, 74)

ARRAY8 answer@@RANDOM_ID_2@@ 8
ARRAY(CREATE8, 8, answer@@RANDOM_ID_2@@)

ARRAY32 answerALL@@RANDOM_ID_3@@ 8
ARRAY(CREATE32, 8, answerALL@@RANDOM_ID_3@@)
DATA8 tmp@@RANDOM_ID_4@@
DATA32 tmp32@@RANDOM_ID_5@@

INPUT_DEVICE(SETUP, 0, @@PORT@@, 1, 0, 2, @ar@@RANDOM_ID_1@@, 5, @answer@@RANDOM_ID_2@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 0, tmp@@RANDOM_ID_4@@)
MOVE8_32(tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
AND32(tmp32@@RANDOM_ID_5@@, 255, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerALL@@RANDOM_ID_3@@, 5, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 1, tmp@@RANDOM_ID_4@@)
MOVE8_32(tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
AND32(tmp32@@RANDOM_ID_5@@, 255, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerALL@@RANDOM_ID_3@@, 4, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 2, tmp@@RANDOM_ID_4@@)
MOVE8_32(tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
AND32(tmp32@@RANDOM_ID_5@@, 255, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerALL@@RANDOM_ID_3@@, 3, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 3, tmp@@RANDOM_ID_4@@)
MOVE8_32(tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
AND32(tmp32@@RANDOM_ID_5@@, 255, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerALL@@RANDOM_ID_3@@, 2, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 4, tmp@@RANDOM_ID_4@@)
MOVE8_32(tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
AND32(tmp32@@RANDOM_ID_5@@, 255, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerALL@@RANDOM_ID_3@@, 1, tmp32@@RANDOM_ID_5@@)

ARRAY_WRITE(ar@@RANDOM_ID_1@@, 0, 8)
ARRAY_WRITE(ar@@RANDOM_ID_1@@, 1, 73)

INPUT_DEVICE(SETUP, 0, @@PORT@@, 1, 0, 2, @ar@@RANDOM_ID_1@@, 1, @answer@@RANDOM_ID_2@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 0, tmp@@RANDOM_ID_4@@)
MOVE8_32(tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerALL@@RANDOM_ID_3@@, 0, tmp32@@RANDOM_ID_5@@)

CALL(assign32Array_EV3_KERNEL_util, answerALL@@RANDOM_ID_3@@, @@RESULT@@)
ARRAY(DELETE, answerALL@@RANDOM_ID_3@@)
ARRAY(DELETE, ar@@RANDOM_ID_1@@)
ARRAY(DELETE, answer@@RANDOM_ID_2@@)
