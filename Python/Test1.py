from Test import Stu


class STU(Stu):
    def __init__(self, name, age, grade,no):
        super().__init__(name, age, grade)
        self.no = no
    def get_name(self):
        return "666" + self._name

class Stu(STU):
    def __init__(self, name, age, grade,no):
        super().__init__(name, age, grade, no)
    def get_no(self):
        return self.no
Stu1 = Stu("John", 12, 85, 1)
def main():
    print(Stu1.__dict__)
    print(STU.__base__.__doc__)
if __name__ == "__main__":
    main()