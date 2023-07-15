import { Module } from '@nestjs/common';
import { MongooseModule } from '@nestjs/mongoose';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { AuthModule } from './auth/auth.module';
import { KomponentModule } from './komponent/komponent.module';
import { ShoplistModule } from './shoplist/shoplist.module';
import { UserModule } from './user/user.module';
import { MqttModule } from './mqtt/mqtt.module';

@Module({
  imports: [
    MongooseModule.forRoot(
      'mongodb+srv://fest121:fest121@robot.bricdil.mongodb.net/',
    ),
    UserModule,
    AuthModule,
    ShoplistModule,
    KomponentModule,
    MqttModule,
  ],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
