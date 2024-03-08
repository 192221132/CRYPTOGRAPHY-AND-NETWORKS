#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define SHA3_STATE_SIZE 1600
#define SHA3_CAPACITY_SIZE 25
#define SHA3_LANE_SIZE 64
#define SHA3_LANE_MASK (SHA3_LANE_SIZE - 1)

typedef struct {
    uint64_t lanes[SHA3_STATE_SIZE];
} sha3_state_t;

void sha3_init(sha3_state_t *state) {
    memset(state->lanes, 0, sizeof(state->lanes));

    for (int i = 0; i < SHA3_STATE_SIZE - SHA3_CAPACITY_SIZE; i++) {
        state->lanes[i] = 1;
    }
}

void sha3_permute(sha3_state_t *state) {
   
}

void sha3_xor_capacity(sha3_state_t *state, const uint64_t *input) {
    for (int i = 0; i < SHA3_CAPACITY_SIZE; i++) {
        state->lanes[i] ^= input[i];
    }
}

int sha3_check_zero_lanes(const sha3_state_t *state) {
    int zero_lanes = 0;

    for (int i = 0; i < SHA3_CAPACITY_SIZE; i++) {
        if (state->lanes[i] == 0) {
            zero_lanes++;
        }
    }

    return zero_lanes;
}

int main() {
    sha3_state_t state;
    sha3_init(&state);

    int iterations = 0;
    int zero_lanes = sha3_check_zero_lanes(&state);

    uint64_t capacity_mask[SHA3_CAPACITY_SIZE] = { 0 };
    for (int i = 0; i < SHA3_CAPACITY_SIZE; i++) {
        capacity_mask[i] = (uint64_t)1 << (SHA3_LANE_SIZE - 1);
    }

    while (zero_lanes > 0) {
        sha3_xor_capacity(&state, capacity_mask);
        zero_lanes = sha3_check_zero_lanes(&state);
        iterations++;
    }

    printf("It took %d iterations to set all the capacity bits.\n", iterations);

    return 0;
}
