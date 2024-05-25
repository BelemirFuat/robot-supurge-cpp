#pragma region
const char one = 66;
const char two = 70;
#pragma endregion

#pragma region "Includes"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <math.h>
#pragma endregion

#pragma region "Classes"
class Robot;
class RobotSweeper;
class House;
class Room;
class Area;
class Obstacle;
#pragma endregion

#pragma region "Functions"
void girisMenu();
void haritayiGoster();
void komutVer();
void dosyayaKaydet();
#pragma endregion

std::list<Obstacle> obstacles;
std::list<Area> areasToClean;
int evX = 0;
int evY = 0;
class Obstacle
{
public:
    int number;
    int x;
    int y;
    Obstacle(int number_, int x_ = 0, int y_ = 0)
    {
        this->number = number_;
        this->x = x_;
        this->y = y_;
    }
};
class TemizlikSonrasiBilgi{

    double harcananSarj;
    int temizlenenAlan;
    int temizlikSuresi;
    std::string temizlikModu;
    int hiz;
    int sarjSayisi;
    std::string temizlenenYer;

    public:
    TemizlikSonrasiBilgi(double harcananSarj_ = 0, int temizlenenAlan_ = 0, int temizlikSuresi_ = 0, std::string temizlikModu_ = "", int hiz_ = 0, int sarjSayisi_ = 0, std::string temizlenenYer_ = "")
    {
        this->harcananSarj = harcananSarj_;
        this->temizlenenAlan = temizlenenAlan_;
        this->temizlikSuresi = temizlikSuresi_;
        this->temizlikModu = temizlikModu_;
        this->hiz = hiz_;
        this->sarjSayisi = sarjSayisi_;
        this->temizlenenYer = temizlenenYer_;
    }
    void setHarcananSarj(double harcananSarj_)
    {
        this->harcananSarj = harcananSarj_;
    }
    void setTemizlenenAlan(int temizlenenAlan_)
    {
        this->temizlenenAlan = temizlenenAlan_;
    }
    void setTemizlikSuresi(int temizlikSuresi_)
    {
        this->temizlikSuresi = temizlikSuresi_;
    }
    double getHarcananSarj()
    {
        return this->harcananSarj;
    }
    int getTemizlenenAlan()
    {
        return this->temizlenenAlan;
    }
    int getTemizlikSuresi()
    {
        return this->temizlikSuresi;
    }
    std::string getTemizlikModu()
    {
        return this->temizlikModu;
    }
    void setTemizlikModu(std::string temizlikModu_)
    {
        this->temizlikModu = temizlikModu_;
    }
    int getHiz()
    {
        return this->hiz;
    }
    void setHiz(int hiz_)
    {
        this->hiz = hiz_;
    }
    int getSarjSayisi()
    {
        return this->sarjSayisi;
    }
    void setSarjSayisi(int sarjSayisi_)
    {
        this->sarjSayisi = sarjSayisi_;
    }
    std::string getTemizlenenYer()
    {
        return this->temizlenenYer;
    }
    void setTemizlenenYer(std::string temizlenenYer_)
    {
        this->temizlenenYer = temizlenenYer_;
    }


    

};
class Robot
{
protected:
    double batteryLife;
    int cleaningArea;
    int cleaningTime;
    int speed;

public:
    Robot(double batteryLife_ = 0, int cleaningArea_ = 0, int cleaningTime_ = 0, int speed_ = 0)
    {
        this->batteryLife = batteryLife_;
        this->cleaningArea = cleaningArea_;
        this->cleaningTime = cleaningTime_;
        this->speed = speed_;
    }

    virtual void move() = 0;
};

class RobotSweeper : public Robot
{
private:
    int currentX;
    int currentY;
    double currentBatteryLife;
    int moppingWater;
    std::list<Obstacle> obstaclesMet;

public:
    RobotSweeper(int currentX_ = 0, int currentY_ = 0, double currentBatteryLife_ = 0,
                 int moppingWater_ = 0, double batteryLife_ = 0, int cleaningArea_ = 0, int cleaningTime_ = 0, int speed_ = 0)
    {
        this->currentX = currentX_;
        this->currentY = currentY_;
        this->currentBatteryLife = currentBatteryLife_;
        this->moppingWater = moppingWater_;
        this->batteryLife = batteryLife_;
        this->cleaningArea = cleaningArea_;
        this->cleaningTime = cleaningTime_;
        this->speed = speed_;
    }
    RobotSweeper(const RobotSweeper &other)
        : Robot(other), currentX(other.currentX), currentY(other.currentY), currentBatteryLife(other.currentBatteryLife), moppingWater(other.moppingWater) {}

    RobotSweeper &operator=(const RobotSweeper &other)
    {
        if (this != &other)
        {
            Robot::operator=(other);
            currentX = other.currentX;
            currentY = other.currentY;
            currentBatteryLife = other.currentBatteryLife;
            moppingWater = other.moppingWater;
        }
        return *this;
    }
    int getCurrentX()
    {
        return this->currentX;
    }
    int getCurrentY()
    {
        return this->currentY;
    }
    void setSpeed(int speed_)
    {
        this->speed = speed_;
    }
    int getSpeed()
    {
        return this->speed;
    }
    void durumRaporu()
    {
        std::cout << "Supurgenin Durumu: " << std::endl;
        std::cout << "Konumu: (" << currentX << ", " << currentY << ")" << std::endl;
        std::cout << "Batarya: %" << currentBatteryLife << std::endl;
        std::cout << "Mop: %" << moppingWater << std::endl;
    }
    TemizlikSonrasiBilgi justMove(int hedefX, int hedefY, double sarjCarpani = 1) // sarjCarpani 0 ise supurme veya normal gitme, 0.1 ise mop
    {
        std::cout << "(" << currentX << "," << currentY << ") Noktasindan (" << hedefX << "," << hedefY << ")Noktasina Gidiliyor..." << std::endl;
        double sarj = speed * 0.1 + sarjCarpani;
        int zaman = 2 / speed;
        int toplamHareket = 0;
        int toplamSure = 0;
        bool engel = false;
        int farkX, farkY;
        int sarjSayisi = 0;

        if (hedefX > currentX)
            farkX = 1;
        else
            farkX = -1;

        if (hedefY > currentY)
            farkY = 1;
        else
            farkY = -1;
        // batarya kontrolu, engel kontrolu
        for (int i = 0; i < abs(hedefY - currentY); i++)
        {
            for (int i = 0; i < abs(hedefX - currentX); i++)
            {
                currentBatteryLife -= sarj;
                if (currentBatteryLife <= 5)
                {
                    std::cout << "Batarya Yuzde 5'in Altina Dustu. Supurge Şarj İstasyonuna Dönüyor..." << std::endl;
                    currentBatteryLife = 100;
                    toplamSure += 10;
                    std::cout << "10 dk geçti ve Şarj 100'e ulaştı. Temizliğe Kalındığı Yerden Devam Ediliyor..." << std::endl;
                    sarjSayisi++;
                }
                engel = false;
                for (auto &obstacle : obstacles)
                {
                    if ((currentX + 1 == obstacle.x) && (currentY = obstacle.y))
                    {
                        std::cout << "Engel Var. Konum : (" << obstacle.x << ", " << obstacle.y << ")" << std::endl;
                        engelAtla(toplamHareket, 0, farkX, farkY, sarj);
                        obstaclesMet.push_back(obstacle);
                        engel = true;
                    }
                }
                if (!engel)
                {
                    currentX += farkX;
                    toplamHareket++;
                }
            }
            for (auto &obstacle : obstacles)
            {
                if ((currentY + 1 == obstacle.y) && (currentX = obstacle.x))
                {
                    std::cout << "Engel Var. Konum : (" << obstacle.x << ", " << obstacle.y << ")" << std::endl;
                        obstaclesMet.push_back(obstacle);

                    engelAtla(toplamHareket, 1, farkX, farkY, sarj);
                    engel = true;
                }
            }
            if (!engel)
            {
                currentY += farkY;
                toplamHareket++;
            }
        }
        toplamSure += toplamHareket * zaman;

        TemizlikSonrasiBilgi bilgi(sarj*toplamHareket, toplamHareket, toplamSure, "Supurme", speed, sarjSayisi, "(" + std::to_string(currentX) + "," + std::to_string(currentY) + ") - (" + std::to_string(hedefX) + "," + std::to_string(hedefY) + ")");
        return bilgi;
    }
    void move()
    {
        std::cout << "Lutfen Hareket Modunu ve Gidecegim Konumu giriniz..." << std::endl;
    }
    void setCurrentX(int x)
    {
        this->currentX = x;
    }
    void setCurrentY(int y)
    {
        this->currentY = y;
    }
    TemizlikSonrasiBilgi cleaning(int hedefX, int hedefY)
    {
        std::cout << "Temizlik Yapmak Uzere ";
        TemizlikSonrasiBilgi bilgi;
        bilgi = justMove(hedefX, hedefY, 0);
        bilgi.setTemizlikModu("Supurme");
        std::cout<<"Temizlik Tamamlandi. Yuvaya Dönülüyor..."<<std::endl;
        currentX = 0;
        currentY = 0;
        return bilgi;
    }
    TemizlikSonrasiBilgi mopping(int hedefX, int hedefY)
    {
        std::cout << "Silmek üzere ";
        TemizlikSonrasiBilgi bilgi;
        bilgi = justMove(hedefX, hedefY, 0.1);
        bilgi.setTemizlikModu("Silme");
        std::cout<<"Temizlik Tamamlandi. Yuvaya Dönülüyor..."<<std::endl;
        currentX = 0;
        currentY = 0;
        return bilgi;
    }
    void engelAtla(int &toplamHareket, int eksen, int farkX, int farkY, double sarj) // eksen 0 ise x ekseninde , 1 ise y ekseninde

    {
        if (eksen == 0) // hareket x ekseninde
        {
            if (currentX - evX <= 1) // sağ köşede ilerleniyorsa
            {
                currentX--;
                currentY += 2 * farkY;
                currentX++;
                toplamHareket += 4;
                currentBatteryLife -= sarj * 4;
            }
            else
            {
                currentX++;
                currentY += 2 * farkY;
                currentX--;
                toplamHareket += 4;
                currentBatteryLife -= sarj * 4;
            }
        }
        else
        {
            if (currentY - evY <= 1) // üst köşede ilerleniyorsa
            {
                currentY--;
                currentX += 2 * farkX;
                currentY++;
                toplamHareket += 4;
                currentBatteryLife -= sarj * 4;
            }
            else
            {
                currentY++;
                currentX += 2 * farkX;
                currentY--;
                toplamHareket += 4;
                currentBatteryLife -= sarj * 4;
            }
        }
    }
};

class House
{
protected:
    std::string houseName;
    int x;
    int y;

public:
    std::list<Room> rooms;
    House(std::string name_ = "", int x_ = 0, int y_ = 0)
    {
        this->houseName = name_;
        this->x = x_;
        this->y = y_;
    }
    void setHouseName(std::string name_)
    {
        this->houseName = name_;
    }
    std::string getHouseName()
    {
        return this->houseName;
    }
    int getX()
    {
        return this->x;
    }
    int getY()
    {
        return this->y;
    }
    void setX(int x_)
    {
        this->x = x_;
    }
    void setY(int y_)
    {
        this->y = y_;
    }
};

class Room : public House
{

    std::string roomName;
    int roomNumber;
    int x1;
    int y1;
    int x2;
    int y2;

public:
    Room(std::string name = "", int roomNumber_ = 0, int x1_ = 0, int y1_ = 0, int x2_ = 0,
         int y2_ = 0, std::string name_ = "", int x_ = 0, int y_ = 0)
    {
        this->roomName = name;
        this->roomNumber = roomNumber_;
        this->x1 = x1_;
        this->y1 = y1_;
        this->x2 = x2_;
        this->y2 = y2_;
        this->houseName = name_;
        this->x = x_;
        this->y = y_;
    }
    Room(std::string name = "", int roomNumber_ = 0, int x1_ = 0, int y1_ = 0, int x2_ = 0,
         int y2_ = 0, House ev = House("", 0, 0)) : House(ev.getHouseName(), ev.getX(), ev.getY()) {}

    void setDimensions(int x1_ = 0, int y1_ = 0, int x2_ = 0, int y2_ = 0)
    {
        this->x1 = x1_;
        this->y1 = y1_;
        this->x2 = x2_;
        this->y2 = y2_;
    }
    int getX1()
    {
        return this->x1;
    }
    int getY1()
    {
        return this->y1;
    }
    int getX2()
    {
        return this->x2;
    }
    int getY2()
    {
        return this->y2;
    }
    int getRoomNumber()
    {
        return this->roomNumber;
    }
};

class Area : House
{
    int x1, y1;

public:
    Area(int x1_ = 0, int y1_ = 0)
    {
        this->x1 = x1_;
        this->y1 = y1_;
    }

    Area() : House() {} // Added default constructor for House
};

RobotSweeper supurge(0, 0, 100, 100, 100, 0, 0, 0);
House ev;

std::list<TemizlikSonrasiBilgi> temizlikSonrasiBilgiler;

int main()
{

    std::ifstream file("harita.txt");
    try
    {
        if (!file.is_open())
            throw std::runtime_error("Dosya açılamadı");

        std::string line;
        std::getline(file, line);
        ev.setHouseName(line);

        std::getline(file, line);
        if (line != "Room Number (X1,Y1) (X2,Y2) Obstacle Number (X1,Y1)")
            throw std::runtime_error("Dosya formatı hatalı");
        while (std::getline(file, line))
        {
            if (line.empty())
                continue;

            std::istringstream ss(line);
            std::string token;
            ss >> token; // Get "Room" or "Obstacle"
            if (token == "Room")
            {
                int roomNumber;
                char parenthesis; // To read '(' character
                char comma;
                int x1, y1, x2, y2;
                ss >> roomNumber >> parenthesis >> x1 >> comma >> y1 >> parenthesis >> parenthesis >> x2 >> comma >> y2 >> parenthesis;
                Room oda("", roomNumber, x1, y1, x2, y2, ev.getHouseName(), x2, y2);
                ev.rooms.push_back(oda);
                std::cout << std::endl;
                // Update house dimensions if necessary
                ev.setX(std::max(ev.getX(), x2));
                ev.setY(std::max(ev.getY(), y2));
                ss >> token;
            }
            if (token == "Obstacle")
            {
                int obstacleNumber;
                char parenthesis; // To read '(' character
                int x, y;
                char comma;
                ss >> obstacleNumber >> parenthesis >> x >> comma >> y >> parenthesis;
                obstacles.push_back(Obstacle(obstacleNumber, x, y));
            }
        }
        evX = ev.getX();
        evY = ev.getY();
        while (true)
            girisMenu();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Hata: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}

void girisMenu()
{
    std::cout << "1. Supurgenin Durumunu Goruntule" << std::endl;
    std::cout << "2. Haritayi Goruntule" << std::endl;
    std::cout << "3. Supurgeye Komut Ver" << std::endl;
    std::cout << "-1. Cikis" << std::endl;
    int secim;
    std::cout << "Buyrun Secin: ";
    std::cin >> secim;
    if (secim == 1)
        supurge.durumRaporu();
    else if (secim == 2)
        haritayiGoster();
    else if (secim == 3)
        komutVer();
    else if (secim == -1)
    {
        exit(0);
        dosyayaKaydet();
    }
    else
        std::cout << "Hatali Giris tekrar deneyiniz." << std::endl;
}

void haritayiGoster()
{
    std::cout << "Odalar: " << std::endl;
    for (auto room : ev.rooms)
    {
        std::cout << "Oda " << room.getRoomNumber() << ": (" << room.getX1() << "," << room.getY1() << ") (" << room.getX2() << "," << room.getY2() << ")" << std::endl;
    }
    std::cout << "Engeller: " << std::endl;
    for (auto obstacle : obstacles)
    {
        std::cout << "Engel " << obstacle.number << ": (" << obstacle.x << "," << obstacle.y << ")" << std::endl;
    }
}

void komutVer()
{
    int secim;
    std::cout << "1. Bir Noktaya kadar Temizleme Modu" << std::endl;
    std::cout << "2. Bir Noktaya kadar Temizleme ve Silme Modu" << std::endl;
    std::cout << "3. Tüm evi Temizleme Modu" << std::endl;
    std::cout << "4. Tüm evi Temizleme Ve Silme Modu" << std::endl;
    std::cout << "5. Robotun Hızını Ayarlama" << std::endl;
    std::cout << "6. Bir Bölgeyi Temizleme Modu" << std::endl;
    std::cout << "7. Bir Bölgeyi Temizleme Ve Silme Modu" << std::endl;
    std::cout << "-1. Onceki Menu" << std::endl;
    std::cout << "Buyrun secin: " << std::endl;

    std::cin >> secim;

    if (secim == 1)
    {
        int x, y;
        std::cout << "Hedef Noktayı Giriniz: (x y)" << std::endl;
        std::cin >> x >> y;
        TemizlikSonrasiBilgi bilgi =supurge.justMove(x, y);
        temizlikSonrasiBilgiler.push_back(bilgi);
    }
    else if (secim == 2)
    {
        int x, y;
        std::cout << "Hedef Noktayı Giriniz: (x y)" << std::endl;
        std::cin >> x >> y;
        TemizlikSonrasiBilgi bilgi =supurge.mopping(x, y);
        temizlikSonrasiBilgiler.push_back(bilgi);

    }
    else if (secim == 3)
    {
        TemizlikSonrasiBilgi bilgi =supurge.cleaning(evX, evY);
        temizlikSonrasiBilgiler.push_back(bilgi);

    }
    else if (secim == 4)
    {
        TemizlikSonrasiBilgi bilgi =supurge.mopping(evX, evY);
        temizlikSonrasiBilgiler.push_back(bilgi);

    }
    else if (secim == 5)
    {
        int speed;
        std::cout << "Hızı Giriniz: " << std::endl;
        std::cin >> speed;
        supurge.setSpeed(speed);
    }else if(secim == 6)
    {
        int x1, y1, x2, y2;
        std::cout << "Bölgenin Köşelerini Giriniz: (x1 y1 x2 y2)" << std::endl;
        std::cin >> x1 >> y1 >> x2 >> y2;
        supurge.setCurrentX(x1);
        supurge.setCurrentY(y1);
        
        TemizlikSonrasiBilgi bilgi =supurge.cleaning(x2, y2);
        std::cout<<"Harcanan Enerji: "<<bilgi.getHarcananSarj()<<std::endl;
        std::cout<<"Temizlenen Alan: "<<bilgi.getTemizlenenAlan()<<std::endl;
        std::cout<<"Temizlik Süresi: "<<bilgi.getTemizlikSuresi()<<std::endl;
        temizlikSonrasiBilgiler.push_back(bilgi);

    }
    else if(secim == 7)
    {
        int x1, y1, x2, y2;
        std::cout << "Bölgenin Köşelerini Giriniz: (x1 y1 x2 y2)" << std::endl;
        std::cin >> x1 >> y1 >> x2 >> y2;
        supurge.setCurrentX(x1);
        supurge.setCurrentY(y1);
        TemizlikSonrasiBilgi bilgi =supurge.mopping(x2, y2);

        std::cout<<"Harcanan Enerji: "<<bilgi.getHarcananSarj()<<std::endl;
        std::cout<<"Temizlenen Alan: "<<bilgi.getTemizlenenAlan()<<std::endl;
        std::cout<<"Temizlik Süresi: "<<bilgi.getTemizlikSuresi()<<std::endl;
        temizlikSonrasiBilgiler.push_back(bilgi);

    }
    else if (secim == -1)
    {
        girisMenu();
    }
    else
    {
        std::cout << "Hatalı Giriş Yaptınız. Tekrar Deneyiniz." << std::endl;
    }
}
void dosyayaKaydet()
{
    std::ofstream file("sonuc.txt");
    file << "Temizlik Sonrası Bilgiler: " << std::endl;
    for (auto bilgi : temizlikSonrasiBilgiler)
    {
        file << "Harcanan Enerji: " << bilgi.getHarcananSarj() << std::endl;
        file << "Temizlenen Alan: " << bilgi.getTemizlenenAlan() << std::endl;
        file << "Temizlik Süresi: " << bilgi.getTemizlikSuresi() << std::endl;
        file << "Temizlik Modu: " << bilgi.getTemizlikModu() << std::endl;
        file << "Hız: " << bilgi.getHiz() << std::endl;
        file << "Şarj Sayısı: " << bilgi.getSarjSayisi() << std::endl;
        file << "Temizlenen Yer: " << bilgi.getTemizlenenYer() << std::endl;
    }
    file<<std::endl;
    file.close();
}