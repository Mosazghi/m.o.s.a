import { Module } from '@nestjs/common';
import { MongooseModule } from '@nestjs/mongoose';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { AuthModule } from './auth/auth.module';
import { KoordinaterModule } from './koordinater/koordinater.module';
import { UserModule } from './user/user.module';
import { ShoplistModule } from './shoplist/shoplist.module';

@Module({
  imports: [
    KoordinaterModule,
    MongooseModule.forRoot(
      'mongodb+srv://fest121:fest121@robot.bricdil.mongodb.net/',
    ),
    UserModule,
    AuthModule,
    ShoplistModule,
  ],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
