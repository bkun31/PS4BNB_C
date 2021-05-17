#!/bin/sh

#run unit tests (all by default)
#Usage : $0 [test_num]
#test_num value :
# 1 test block
# 2 test blockchain
# 3 test transaction
# 4 test user
# 5 test bnb
# 6 test cheaters
# 7 test config
# 8 test sha256

cd $(dirname $0)

if [ $# -ge 2 ]; then
    echo "Usage : $0 [test_num]" >&2
    exit 1
fi

if [ $# -eq 0 ]; then
    gcc -Wall -Werror -std=c99 -g ../src/block.c ../src/skiplist.c ../src/rng.c ../src/sha256_utils.c ../src/sha256.c ../src/transaction.c ../src/queue.c ../src/user.c ../src/bnb.c block-tests/test_block.c -o block-tests/test_block
    gcc -Wall -Werror -std=c99 -g ../src/blockchain.c ../src/block.c ../src/transaction.c ../src/queue.c ../src/user.c ../src/bnb.c ../src/skiplist.c ../src/rng.c ../src/sha256_utils.c ../src/sha256.c blockchain-tests/test_blockchain.c -o blockchain-tests/test_blockchain
    gcc -Wall -Werror -std=c99 -g ../src/transaction.c ../src/user.c ../src/bnb.c ../src/queue.c ../src/skiplist.c ../src/rng.c transaction-tests/test_transaction.c ../src/sha256_utils.c ../src/sha256.c -o transaction-tests/test_transaction
    gcc -Wall -Werror -std=c99 -g ../src/user.c ../src/bnb.c ../src/queue.c user-tests/test_user.c -o user-tests/test_user
    gcc -Wall -Werror -std=c99 -g ../src/bnb.c bnb-tests/test_bnb.c -o bnb-tests/test_bnb
    gcc -Wall -Werror -std=c99 -g ../src/cheaters.c ../src/skiplist.c ../src/rng.c ../src/user.c ../src/transaction.c ../src/blockchain.c ../src/block.c ../src/queue.c ../src/bnb.c ../src/sha256_utils.c ../src/sha256.c cheaters-tests/test_cheaters.c -o cheaters-tests/test_cheaters
    gcc -Wall -Werror -std=c99 -g ../src/config.c ../src/bnb.c config-tests/test_config.c -o config-tests/test_config
    gcc -Wall -Werror -std=c99 -g ../src/sha256.c ../src/sha256_utils.c sha256-tests/test_sha.c -o sha256-tests/test_sha

    cd block-tests/
    printf "\n---------- Run test_block ---------\n\n"
    ./test_block
    rm ./test_block

    cd ../blockchain-tests/
    printf "\n---------- Run test_blockchain ---------\n\n"
    ./test_blockchain
    rm ./test_blockchain

    cd ../transaction-tests/
    printf "\n---------- Run test_transaction ---------\n\n"
    ./test_transaction
    rm ./test_transaction

    cd ../user-tests/
    printf "\n---------- Run test_user ---------\n\n"
    ./test_user
    rm ./test_user

    cd ../bnb-tests/
    printf "\n---------- Run test_bnb ---------\n\n"
    ./test_bnb
    rm ./test_bnb

    cd ../cheaters-tests/
    printf "\n---------- Run test_cheaters ---------\n\n"
    ./test_cheaters
    rm ./test_cheaters

    cd ../../
    printf "\n---------- Run test_config ---------\n\n"
    ./test/config-tests/test_config
    rm ./test/config-tests/test_config

    cd test/sha256-tests/
    printf "\n---------- Run test_sha ---------\n\n"
    ./test_sha
    rm ./test_sha

else
    if [ "1" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 -g ../src/block.c ../src/skiplist.c ../src/rng.c ../src/sha256_utils.c ../src/sha256.c ../src/transaction.c ../src/queue.c ../src/user.c ../src/bnb.c block-tests/test_block.c -o block-tests/test_block
        cd block-tests/

        printf "\n---------- Run test_block ---------\n\n"

        ./test_block
        rm ./test_block

    elif [ "2" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 -g ../src/blockchain.c ../src/block.c ../src/transaction.c ../src/queue.c ../src/user.c ../src/bnb.c ../src/skiplist.c ../src/rng.c ../src/sha256_utils.c ../src/sha256.c blockchain-tests/test_blockchain.c -o blockchain-tests/test_blockchain
        cd blockchain-tests/

        printf "\n---------- Run test_blockchain ---------\n\n"

        ./test_blockchain
        rm ./test_blockchain

    elif [ "3" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 -g ../src/transaction.c ../src/user.c ../src/bnb.c ../src/queue.c ../src/skiplist.c ../src/rng.c transaction-tests/test_transaction.c ../src/sha256_utils.c ../src/sha256.c -o transaction-tests/test_transaction
        cd transaction-tests/

        printf "\n---------- Run test_transaction ---------\n\n"

        ./test_transaction
        rm ./test_transaction

    elif [ "4" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 -g ../src/user.c ../src/bnb.c ../src/queue.c user-tests/test_user.c -o user-tests/test_user
        cd user-tests/

        printf "\n---------- Run test_user ---------\n\n"

        ./test_user
        rm ./test_user

    elif [ "5" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 -g ../src/bnb.c bnb-tests/test_bnb.c -o bnb-tests/test_bnb
        cd bnb-tests/

        printf "\n---------- Run test_bnb ---------\n\n"

        ./test_bnb
        rm ./test_bnb

    elif [ "6" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 -g ../src/cheaters.c ../src/skiplist.c ../src/rng.c ../src/user.c ../src/transaction.c ../src/blockchain.c ../src/block.c ../src/queue.c ../src/bnb.c ../src/sha256_utils.c ../src/sha256.c cheaters-tests/test_cheaters.c -o cheaters-tests/test_cheaters
        cd cheaters-tests/

        printf "\n---------- Run test_cheaters ---------\n\n"
        ./test_cheaters
        rm ./test_cheaters

    elif [ "7" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 -g ../src/config.c ../src/bnb.c config-tests/test_config.c -o config-tests/test_config
        cd ../

        printf "\n---------- Run test_config ---------\n\n"
        ./test/config-tests/test_config
        rm ./test/config-tests/test_config

    elif [ "8" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 -g ../src/sha256.c ../src/sha256_utils.c sha256-tests/test_sha.c -o sha256-tests/test_sha
        cd sha256-tests/

        printf "\n---------- Run test_sha ---------\n\n"
        ./test_sha
        rm ./test_sha

    fi

fi

exit 0
