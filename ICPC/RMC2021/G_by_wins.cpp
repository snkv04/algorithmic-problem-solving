#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    /*
    - problem:
        - we have a game, where we play matches. on each match, we either win or lose. if we win, we either get
        a prize or we don't get a prize. if we get a prize, we either get the gorilla suit or we don't get the
        gorilla suit.
        - the probability that we win/lose a match is fixed. the probability that a given prize is the gorilla
        suit is fixed. however, if we let P = probability that we get a prize after winning, then P increases
        by a different amount after a match if we win or lose.
        - what's the expected number of matches until we get the gorilla suit?
    - solution:
        - since the probability of a prize being the gorilla suit is fixed, that follows a geometric distribution,
        so we can just find the expected value of num matches until prize and multiply that by 1 / G.
        - how to find EV of num matches until prize? let X = match on which we get our first prize. then we
        are trying to find
        0 * P(X=0) + 1 * P(X=1) + ... + 99 * P(X=99) + 100 * P(X=100) + 101 * P(X=101) + 102 * P(X=102) + ...
        - we can find the terms until 100 as follows:
            - we can use DP. keep track of the current number of matches, what the probability P is (or, alternatively,
            the number of wins; this is important because it determines our transition probabilities), and whether we've
            not gotten any prize or gotten exactly 1 prize. we don't care about getting multiple prizes, since we want
            to find P(X = x), not P(X <= x).
            - basically, we intuitively know that there are multiple cases in which we get a prize after exactly
            x matches. so, we enumerate them all (through the use of the number of wins we've gotten, or our current
            probability P), and sum up the probabilities of those cases.
        - we can find the terms after 100 as follows:
            - observe that it's just a tail expected value. if we sum all of the probability terms up,
            then that's just equal to the probability that we never got a prize in the first 100 matches:
            a tail probability. in other words, the prob that any of those cases even happen is equal to
            the tail prob.
            - so, we can rewrite
            101 * P(X=101) + 102 * P(X=102) + ... =
            P(X > 100) * E[X | X > 100].
            - that first term is our tail probability. how do we find the second part? note that after 100 matches,
            P = 100. as soon as we get our next win, we're done. that's just a geometric distribution. so if we let
            Y = number of matches until a win, then E[X | X > 100] = 100 + E[Y].
    - summary:
        - we basically just want EV of number of matches until a prize.
        - we have an infinite number of cases of how many matches it'll take. let's deal with the first 100 cases,
        since each value can have a different P(prize | win), so we need DP.
        - our DP state mainly keeps track of the probability that we've never gotten a prize; if we get a prize,
        we move that to a different state which is used for EV but not for future DP states.
        - for the remaining infinite terms, we condense those cases into a single case by finding the EV of those
        cases. this is easy since P(prize|win) is 1.0 at this point, and "num matches until win" follows a geometric
        distribution. we assume we haven't gotten a prize in the first 100 matches, so we shift that EV over by 100,
        and multiply by the probability that we even land in one of those cases in the first place (i.e., that we
        haven't gotten a prize in the first 100 matches).
    - notes:
        - why is keeping track of (matches, wins) better than keeping track of (matches, probability of prize)?
        because: for the latter, the implementation is more difficult. they are both correct, but specifically,
        the former is better because we only ever need to draw from (i-1, j) or (i-1, j-1). for the latter, we
        know that the probability is capped at 100, so if P = 100, then we have to draw from ALL of the valid
        (i-1, j) such that (j + (dL or dW)) gets set to 100. that's more states to draw from, and harder to
        code correctly; instead, go with the easier-to-code solution.
        - this entire problem is just a series of breaking things into cases:
            - we break down "num matches until prize" into an infinite number of cases
            - we divide those cases into two cases
            - for the first case, we have 101 possible values of number of matches; each of those is further
            separated out into 101 DP states based on how many matches we've won, and each of those is further
            broken down into "we've never gotten a prize" and "we got a prize exactly here"
            - for the second case, we condense all cases into one case by using a representative value (the
            expected value)
        - yes, it's perfectly possible that before 100 matches, our P(prize | win) = 1.0 already. however, that
        doesn't mean that it HAS to be computed with the tail probability. using our DP states is still, at the
        least, correct. we just know with a guarantee that after 100 matches, P(prize | win) is surely 1.0, but
        even if it happens before then it's fine.
    */

    array<ld, 4> input;
    for (int i = 0; i < 4; ++i) {
        cin >> input[i];
        input[i] /= 100.0;
    }
    auto [dL, dW, G, L] = input;
    ld W = 1.0 - L;

    // mem[i][j][0] := probability of not having won any prizes after playing i matches and winning j matches
    // mem[i][j][1] := probability of winning a prize on the i'th match after winning j matches
    ld mem[101][101][2];
    for (int i = 0; i <= 100; ++i) for (int j = 0; j <= 100; ++j) fill(mem[i][j], mem[i][j] + 2, 0);
    mem[0][0][0] = 1.0;
    for (int i = 1; i <= 100; ++i) {
        for (int j = 0; j <= i; ++j) {
            // lose
            mem[i][j][0] += L * mem[i - 1][j][0];

            // win and no prize
            ld p_prize = min((ld) 1.0, (j - 1) * dW + (i - j) * dL);
            ld p_no_prize = 1.0 - p_prize;
            if (j) {
                mem[i][j][0] += W * p_no_prize * mem[i - 1][j - 1][0];
            }

            // win and get prize
            if (j) {
                mem[i][j][1] += W * p_prize * mem[i - 1][j - 1][0];
            }
        }
    }

    ld expected_value = 0.0;
    for (int i = 0; i <= 100; ++i) {
        ld prob = 0.0;
        for (int j = 0; j <= 100; ++j) {
            prob += mem[i][j][1];
        }
        expected_value += prob * i;
    }
    ld tail_prob = 0.0;
    for (int j = 0; j <= 100; ++j) {
        tail_prob += mem[100][j][0];
    }
    expected_value += tail_prob * (100 + 1.0 / W);
    
    ld ans = expected_value * 1.0 / G;
    cout << fixed << setprecision(12) << ans << endl;
}
