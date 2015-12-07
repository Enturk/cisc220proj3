/* this will generate the moves
 *
 * 1. compute each corss-check
 * 2. compute the anchor positions
 * 3. compute all possible moves for rows/cols
 *   a. use LeftPart() and ExtendRight() from the paper
 * 4. Score all the moves
 * 5. Sort the moves
 * 6. return an array of moves
 * If this function becomes too monolithic, steps 4+5 can
 * be extracted to their own functions
 */
