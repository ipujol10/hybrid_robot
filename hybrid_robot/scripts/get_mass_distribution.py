class Box:
    height = 0
    width = 0
    length = 0
    volume = 0
    mass = 0

    def __init__(self, height, width, length):
        self.height = height
        self.width = width
        self.length = length
        self.volume = self.get_volume()

    def get_volume(self):
        return self.height * self.width * self.length

    @staticmethod
    def obtain_mass(total_mass, list_boxes):
        total_volume = sum([box.volume for box in list_boxes])
        for box in list_boxes:
            box.mass = total_mass * box.volume / total_volume


def main():
    total_mass = 0.05285  # grams
    width = 0.1772
    high = Box(0.0801, width, 0.01)
    short = Box(0.012, width, 0.14)
    Box.obtain_mass(total_mass, [high, short])
    print('Base high = {} kg'.format(high.mass))
    print('Base short = {} kg'.format(short.mass))


if __name__ == "__main__":
    main()
