import { Module } from '@nestjs/common';
import { MongooseModule } from '@nestjs/mongoose';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { AuthModule } from './auth/auth.module';
import { KomponentModule } from './komponent/komponent.module';
import { ShoplistModule } from './shoplist/shoplist.module';
import { UserModule } from './user/user.module';

@Module({
  imports: [
    MongooseModule.forRoot(
      'mongodb+srv://Abdi:Abdi10002@cluster0.2ysdgp5.mongodb.net/'
      ,
    ),
    UserModule,
    AuthModule,
    ShoplistModule,
    KomponentModule,
  ],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
