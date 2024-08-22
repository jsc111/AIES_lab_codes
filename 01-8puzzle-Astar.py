class Node:
    def __init__(self, data, level, fval):
        self.data = data
        self.level = level
        self.fval = fval

    def generate_children(self):
        x, y = self.find_blank()
        directions = [(x, y-1), (x, y+1), (x-1, y), (x+1, y)]
        children = []
        for new_x, new_y in directions:
            child_data = self.move_blank(x, y, new_x, new_y)
            if child_data:
                children.append(Node(child_data, self.level + 1, 0))
        return children

    def move_blank(self, x1, y1, x2, y2):
        if 0 <= x2 < len(self.data) and 0 <= y2 < len(self.data):
            new_data = [row[:] for row in self.data]
            new_data[x1][y1], new_data[x2][y2] = new_data[x2][y2], new_data[x1][y1]
            return new_data
        return None

    def find_blank(self):
        for i, row in enumerate(self.data):
            for j, value in enumerate(row):
                if value == '_':
                    return i, j


class Puzzle:
    def __init__(self, size):
        self.size = size
        self.open = []
        self.closed = []

    def input_puzzle(self, prompt):
        print(prompt)
        return [input().split() for _ in range(self.size)]

    def calculate_f(self, start, goal):
        return self.calculate_h(start.data, goal) + start.level

    def calculate_h(self, start, goal):
        return sum(start[i][j] != goal[i][j] and start[i][j] != '_' for i in range(self.size) for j in range(self.size))

    def solve(self):
        start = self.input_puzzle("Enter the start state matrix:")
        goal = self.input_puzzle("Enter the goal state matrix:")

        start_node = Node(start, 0, 0)
        start_node.fval = self.calculate_f(start_node, goal)
        self.open.append(start_node)

        while self.open:
            current = self.open.pop(0)
            print("\n  | \n  | \n \\'/ \n")
            for row in current.data:
                print(" ".join(row))

            if self.calculate_h(current.data, goal) == 0:
                break

            for child in current.generate_children():
                child.fval = self.calculate_f(child, goal)
                self.open.append(child)
            self.closed.append(current)
            self.open.sort(key=lambda node: node.fval)

if __name__ == "__main__":
    puzzle = Puzzle(3)
    puzzle.solve()