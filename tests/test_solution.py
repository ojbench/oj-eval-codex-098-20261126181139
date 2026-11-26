"""Check all seven-node BST shapes and ranks against sorted values."""
import itertools
import subprocess
import sys


def level_order(values):
    root = None
    for value in values:
        if root is None:
            root = [value, None, None]
            continue
        node = root
        while True:
            side = 1 if value < node[0] else 2
            if node[side] is None:
                node[side] = [value, None, None]
                break
            node = node[side]
    queue = [root]
    result = []
    for node in queue:
        result.append(node[0])
        queue.extend(child for child in node[1:] if child is not None)
    return tuple(result)


def check(executable, values, rank, expected):
    data = "\n".join(map(str, (*values, rank))) + "\n"
    result = subprocess.run(
        [executable], input=data, text=True, capture_output=True, check=True
    )
    assert result.stdout.strip() == str(expected), (data, result.stdout, expected)


def main():
    executable = sys.argv[1] if len(sys.argv) > 1 else "./build/code"
    check(executable, (7, 3, 9, 1, 5, 8, 10), 2, 9)
    values = (-(2**63), -100, -1, 0, 1, 100, 2**63 - 1)
    orders = {level_order(order) for order in itertools.permutations(values)}
    assert len(orders) == 429
    for order in orders:
        for rank in range(1, 8):
            check(executable, order, rank, values[-rank])
    print(f"Passed sample and all {len(orders) * 7} shape/rank cases.")


if __name__ == "__main__":
    main()
