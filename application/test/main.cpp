#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QTimer>


int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    QTimer exitTimer;

    QObject::connect(&exitTimer, &QTimer::timeout, &app, [&]()
    {
        ::testing::InitGoogleTest(&argc, argv);
        auto ret = RUN_ALL_TESTS();
        app.exit(ret);
    });
    exitTimer.setSingleShot(true);
    exitTimer.setInterval(0);
    exitTimer.start();
    return app.exec();
}
