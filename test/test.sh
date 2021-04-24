#!/bin/zsh

#run unit tests (all by default)
#Usage : $0 [test_num]
#test_num value :
# 1 test block
# 2 test blockchain
# 3 test transaction
# 4 test user
# 5 test bnb
# 6 test cheater block
# 7 test cheater transaction
# 8 test config

cd $(dirname $0)

if [ $# -ge 2 ]; then
    echo "Usage : $0 [test_num]" >&2
    exit 1
fi

if [ $# -eq 0 ]; then
    gcc -Wall -Werror -std=c99 -g../src/block.c ../src/skiplist.c ../src/rng.c ../src/sha256_utils.c ../src/sha256.c block-tests/test_block.c -o block-tests/test_block
    gcc -Wall -Werror -std=c99 -g../src/blockchain.c blockchain-tests/test_blockchain.c -o blockchain-tests/test_blockchain
    gcc -Wall -Werror -std=c99 -g ../src/transaction.c transaction-tests/test_transaction.c -o transaction-tests/test_transaction
    gcc -Wall -Werror -std=c99 -g ../src/user.c user-tests/test_user.c -o user-tests/test_user
    gcc -Wall -Werror -std=c99 -g ../src/bnb.c bnb-tests/test_bnb.c -o bnb-tests/test_bnb
    gcc -Wall -Werror -std=c99 -g ../src/cheater_block.c cheater_block-tests/test_cheater_block.c -o cheater_block-tests/test_cheater_block
    gcc -Wall -Werror -std=c99 -g ../src/cheater_transaction.c cheater_transaction-tests/test_cheater_transaction.c -o cheater_transaction-tests/test_cheater_transaction
    gcc -Wall -Werror -std=c99 -g ../src/config.c ../src/bnb.c config-tests/test_config.c -o config-tests/test_config

    cd block_tests/
    echo "Run test_block\n"
    block-tests/test_block

    cd ../blockchain-tests/
    echo "Run test_blockchain\n"
    blockchain-test/test_blockchain

    cd ../transaction-tests/
    echo "Run test_transaction\n"
    transaction-tests/test_transaction

    cd ../user-tests/
    echo "Run test_user\n"
    user-tests/test_user

    cd ../bnb-tests/
    echo "Run test_bnb\n"
    bnb-tests/test_bnb

    cd ../cheater_block-tests/
    echo "Run test_cheater_block\n"
    cheater_block-tests/test_cheater_block

    cd ../cheater_transaction-tests/
    echo "Run test_cheater_transaction\n"
    cheater_transaction-tests/cheater_transaction

    cd ../..
    echo "Run test_config\n"
    ./test/config-tests/test_config

else
    if [ "1" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 ../src/block.c ../src/skiplist.c -g ../src/rng.c ../src/sha256_utils.c ../src/sha256.c ../src/transaction.c ../src/queue.c ../src/user.c ../src/bnb.c block-tests/test_block.c -o block-tests/test_block
        cd block-tests/

        echo "Run test_block\n"

        ./test_block

    elif [ "2" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 ../src/blockchain.c ../src/skiplist.c -g ../src/rng.c ../src/sha256_utils.c ../src/sha256.c blockchain-tests/test_blockchain.c -o blockchain-tests/test_blockchain
        cd blockchain-tests/

        echo "Run test_blockchain\n"

        ./test_blockchain

    elif [ "3" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 ../src/transaction.c ../src/user.c ../src/bnb.c -g ../src/queue.c ../src/skiplist.c ../src/rng.c transaction-tests/test_transaction.c ../src/sha256_utils.c ../src/sha256.c -o transaction-tests/test_transaction
        cd transaction-tests/

        echo "Run test_transaction\n"

        ./test_transaction

    elif [ "4" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 -g ../src/user.c ../src/bnb.c ../src/queue.c user-tests/test_user.c -o user-tests/test_user
        cd user-tests/

        echo "Run test_user\n"

        ./test_user

    elif [ "5" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 -g ../src/bnb.c bnb-tests/test_bnb.c -o bnb-tests/test_bnb
        cd bnb-tests/

        echo "Run test_bnb\n"

        ./test_bnb

    elif [ "6" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 ../src/cheater_block.c ../src/skiplist.c -g ../src/rng.c ../src/sha256_utils.c ../src/sha256.c cheater_block-tests/test_cheater_block.c -o cheater_block-tests/test_cheater_block
        cd cheater_block-tests/

        echo "Run test_cheater_block\n"
        ./test_cheater_block

    elif [ "7" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 ../src/cheater_transaction.c ../src/skiplist.c -g ../src/rng.c ../src/sha256_utils.c ../src/sha256.c cheater_transaction-tests/test_cheater_transaction.c -o cheater_transaction-tests/test_cheater_transaction
        cd cheater_transaction-tests/

        echo "Run test_cheater_transaction\n"
        ./test_cheater_transaction

    elif [ "8" -eq $1 ]; then
        gcc -Wall -Werror -std=c99 -g ../src/config.c ../src/bnb.c config-tests/test_config.c -o config-tests/test_config
        cd ../

        echo "Run test_config\n"
        ./test/config-tests/test_config
    fi
fi

exit 0
